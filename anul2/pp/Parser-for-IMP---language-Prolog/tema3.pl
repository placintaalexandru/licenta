valnum(X):- char_type(X, alnum), char_type(X, ascii).
vother(X):- member(X, [';','<','+','-','*','(',')','{','}']).
validc(X):- valnum(X) ; vother(X) ;  X == '='.

lparseq(['='|L],'==',L).
lparseq([X|L],'=',[X|L]):-dif(X,'=').
lparseq([],'=',[]).

lparsealn([X|L],L2,R,L3):- valnum(X), lparsealn(L, [X|L2], R, L3).
lparsealn([X|L],L2,R,[X|L]):- \+valnum(X), reverse(L2, L3), atom_chars(R, L3).
lparsealn([],L2,R,[]):- reverse(L2, L3), atom_chars(R, L3).

lparse2(['='|L],L2,L3):- lparseq(L,R,L4), lparse2(L4,[R|L2],L3).
lparse2([X|L],L2,L3):- valnum(X),lparsealn(L,[X],R,L4), lparse2(L4,[R|L2],L3).
lparse2([X|L],L2,L3):- vother(X), lparse2(L,[X|L2],L3).
lparse2([X|L],L2,L3):- \+validc(X), lparse2(L,L2,L3).
lparse2([],L2,L3):- reverse(L2,L3).

lparse(S, L):- atom_chars(S, L2), lparse2(L2,[],L),!.  

isNumber(R):- integer(R).
isPlus(R):- atom_string(R, X), X = "+".
isMinus(R):- atom_string(R, X), X = "-".
isStar(R):- atom_string(R, X), X = "*".
isReturn(R):- atom_string(R, X), X = "return".
isFor(R):- atom_string(R, X), X = "for".
isIf(R):- atom_string(R, X), X = "if".
isAssert(R):- atom_string(R, X), X = "assert".
isSemicolon(R):- atom_string(R, X), X = ";".
isLess(R):- atom_string(R, X), X = "<".

hasOnlyChars([]).
hasOnlyChars([H | T]):- not(char_type(H, digit)), hasOnlyChars(T), !.

isValidName(R):- atom_chars(R, Chars), hasOnlyChars(Chars), !.
isVar(R):- not(isNumber(R)), not(isPlus(R)), not(isMinus(R)), not(isStar(R)),
			not(isReturn(R)), not(isFor(R)), not(isIf(R)), not(isAssert(R)), isValidName(R), !.


%PREDICATE DE PARSAT EXPRESII

%Predicate de parsat token-uri

parseVal([H | T], O, R):- atom_number(H, R1), O = val(R1), R = T, !.
parseVar([H | T], O, R):- isVar(H), atom_string(H, R1), O = var(R1), R = T, !.
parseChar(C, [C | T], C, T).
parseTok(L, O, R):- (parseVal(L, O, R) ; parseVar(L, O, R)), !.


%Predicate de parsat expresii de inmultire

parseME(L, mult(X, Y), R):- parseTok(L, X, R1), parseChar(*, R1, _, R2), parseME(R2, Y, R), !.
parseME(L, O, R):- parseTok(L, O, R).


%Predicate de parsat expresii aritmetice: adunare, scadere si inmultire

parseAE([; | T], O, O, [; | T]).
parseAE([')' | T], O, O, [')' | T]).
parseAE([< | T], O, O, [< | T]).
parseAE([== | T], O, O, [== | T]).
parseAE(L, O, TN, R):- parseChar(*, L, _, R1), parseME(R1, O1, R2), parseAE(R2, O, mult(TN, O1), R), !.
parseAE(L, O, TN, R):- parseChar(+, L, _, R1), parseME(R1, O1, R2), parseAE(R2, O, add(TN, O1), R), !.
parseAE(L, O, TN, R):- parseChar(-, L, _, R1), parseME(R1, O1, R2), parseAE(R2, O, sub(TN, O1), R), !.
parseArithExpr(L, O, R):- parseTok(L, TN, R1), parseAE(R1, O, TN, R2), R = R2, !.


%Predicate de parsat expresii de comparare

parseCE([; | T], O, O, [; | T]).
parseCE([')' | T], O, O, [')' | T]).
parseCE(L, O, [], R):- parseArithExpr(L, O, R), !.
parseCE(L, O, TN, R):- parseChar(<, L, _, R1), parseArithExpr(R1, E1, R2), parseCE(R2, O, less(TN, E1), R), !.
parseCE(L, O, TN, R):- parseChar(==, L, _, R1), parseArithExpr(R1, TN1, R2), parseCE(R2, E1, TN1, R), O = equal(TN, E1), !.
parseCompExpr(L, O, R):- parseArithExpr(L, TN, R1), parseCE(R1, O, TN, R), !.


%Predicate de parsat expresii propriu-zise

parseExpr(L, O, R):- parseCompExpr(L, O, R), !.


%PREDICATE DE PARSAT PROGRAME

%Predicate de parsat body-uri de programe, folosite pt IF si FOR, dar si pt a initia parsarea mare

parseB([], O, TN, _):- reverse(TN, O), !.
parseB(['}' | T], O, TN, ['}' | T]):- reverse(TN, O), !.
parseB(L, O, TN, R):- parseProgram(L, Prog, R1), parseB(R1, O, [Prog | TN], R), !.
parseBody(L, O, R):- parseChar('{', L, _, R1), parseB(R1, O, [], R2), parseChar('}', R2, _, R), !.


%Predicate de parsat programe concrete

parseRet(L, O, R):- parseChar(return, L, _, R1), parseExpr(R1, E, R), O = ret(E), !.

parseAsign(L, O, R):- parseVar(L, O1, R1), parseChar(=, R1, _, R2), parseExpr(R2, E, R), O = asgn(O1, E), !.

parseAssert(L, O, R):- parseChar(assert, L, _, R1), parseChar('(', R1, _, R2), parseExpr(R2, E, R3), O = assert(E),
						parseChar(')', R3, _, R), !.

parseIf(L, O, R):- parseChar(if, L, _, R1), parseChar('(', R1, _, R2), parseExpr(R2, Cond, R3), parseChar(')', R3, _, R4),
					parseChar(then, R4, _, R5), parseBody(R5, IfBody, R6), parseChar(else, R6, _, R7), parseBody(R7, ElseBody, R),
					O = ifProgram(Cond, IfBody, ElseBody), !.

parseFor(L, O, R):- parseChar(for, L, _, R1), parseChar('(', R1, _, R2), parseAsign(R2, Asgn, R3), parseChar(;, R3, _, R4),
					parseExpr(R4, Cond, R5), parseChar(;, R5, _, R6), parseAsign(R6, Increment, R7), parseChar(')', R7, _, R8),
					parseBody(R8, ForBody, R), O = forProgram(Asgn, Cond, Increment, ForBody), !.


%Predicate de parsat programe propriu-zise

parseProgram(L, O, R):- (((parseRet(L, O, R1) ; parseAssert(L, O, R1) ; parseAsign(L, O, R1)), parseChar(;, R1, _, R)) ; 
						parseIf(L, O, R) ; parseFor(L, O, R) ; (parseChar(;, L, _, R), O = [])), !.


%PREDICATE DE EVALUAT PROGRAME

%Predicate de gasit valorile variabilelor in mapa de variabilelor

findVal(_, [], error('e')).
findVal(VarName, [H | _], R):- H = pair(Name, Value), VarName = Name, R = Value, !.
findVal(VarName, [_ | T], R):- findVal(VarName, T, R), !.

%Predicate de evaluat expresii

evalExpr(P, VarMap, R):- P = var(X), findVal(X, VarMap, R), !.
evalExpr(P, _, R):- P = val(X), R = X, !.

evalExpr(E, VarMap, R):- E = add(Left, Right), evalExpr(Left, VarMap, R1), evalExpr(Right, VarMap, R2),
						(R1 = error('e') ; R2 = error('e')), R = error('e'), !.
evalExpr(E, VarMap, R):- E = add(Left, Right), evalExpr(Left, VarMap, R1), evalExpr(Right, VarMap, R2), R is R1 + R2, !.

evalExpr(E, VarMap, R):- E = mult(Left, Right), evalExpr(Left, VarMap, R1), evalExpr(Right, VarMap, R2),
						(R1 = error('e') ; R2 = error('e')), R = error('e'), !.
evalExpr(E, VarMap, R):- E = mult(Left, Right), evalExpr(Left, VarMap, R1), evalExpr(Right, VarMap, R2), R is R1 * R2, !.

evalExpr(E, VarMap, R):- E = sub(Left, Right), evalExpr(Left, VarMap, R1), evalExpr(Right, VarMap, R2),
						(R1 = error('e') ; R2 = error('e')), R = error('e'), !.
evalExpr(E, VarMap, R):- E = sub(Left, Right), evalExpr(Left, VarMap, R1), evalExpr(Right, VarMap, R2), R is R1 - R2, !.

evalExpr(E, VarMap, R):- E = less(Left, Right), evalExpr(Left, VarMap, R1), evalExpr(Right, VarMap, R2),
						(R1 = error('e') ; R2 = error('e')), R = error('e'), !.
evalExpr(E, VarMap, R):- E = less(Left, Right), evalExpr(Left, VarMap, R1), evalExpr(Right, VarMap, R2), R1 < R2, R = 1, !.
evalExpr(E, VarMap, R):- E = less(Left, Right), evalExpr(Left, VarMap, R1), evalExpr(Right, VarMap, R2), R1 >= R2, R = 0, !.

evalExpr(E, VarMap, R):- E = equal(Left, Right), evalExpr(Left, VarMap, R1), evalExpr(Right, VarMap, R2),
						(R1 = error('e') ; R2 = error('e')), R = error('e'), !.
evalExpr(E, VarMap, R):- E = equal(Left, Right), evalExpr(Left, VarMap, R1), evalExpr(Right, VarMap, R2), R1 =:= R2, R is 1, !.
evalExpr(E, VarMap, R):- E = equal(Left, Right), evalExpr(Left, VarMap, R1), evalExpr(Right, VarMap, R2),
						((R1 < R2) ; (R1 > R2)), R is 0, !.


%Predicate de evaluat programe propriu-zise

uniqueInsert(Name, Value, [], ACC, R):- R = [pair(Name, Value) | ACC], !.
uniqueInsert(Name, Value, [H | T], ACC, R):- H = pair(N1, _), Name = N1, append([pair(Name, Value) | ACC], T, R), !.
uniqueInsert(Name, Value, [H | T], ACC, R):- H = pair(N1, _), Name \= N1, uniqueInsert(Name, Value, T, [H | ACC], R), !.

evalProg([], VarMap, VarMap).
evalProg([[] | T], VarMap, O):- evalProg(T, VarMap, O), !.
evalProg([H | _], VarMap, O):- H = ret(Expr), evalExpr(Expr, VarMap, O), !.

evalProg([H | _], VarMap, O):- H = asgn(var(_), Expr), evalExpr(Expr, VarMap, Value), Value = error('e'), O = error('e'), !.
evalProg([H | T], VarMap, O):- H = asgn(var(Name), Expr), evalExpr(Expr, VarMap, Value), 
 								uniqueInsert(Name, Value, VarMap, [], NewMap),
 								evalProg(T, NewMap, O), !.

evalProg([H | _], VarMap, O):- H = assert(Expr), evalExpr(Expr, VarMap, Value), Value = error('e'), O = error('e'), !.
evalProg([H | _], VarMap, O):- H = assert(Expr), evalExpr(Expr, VarMap, Value), Value =:= 0, O = error('a'), !.
evalProg([H | T], VarMap, O):- H = assert(Expr), evalExpr(Expr, VarMap, Value), Value =:= 1, evalProg(T, VarMap, O), !.

evalProg([H | _], VarMap, O):- H = ifProgram(Cond, _, _), evalExpr(Cond, VarMap, Value), Value = error('e'), O = error('e'), !.
evalProg([H | _], VarMap, O):- H = ifProgram(Cond, IfBody, _), evalExpr(Cond, VarMap, Value), Value =:= 1,
								evalProg(IfBody, VarMap, O1), O1 = error(X), O = error(X), !.
evalProg([H | T], VarMap, O):- H = ifProgram(Cond, IfBody, _), evalExpr(Cond, VarMap, Value), Value =:= 1,
								evalProg(IfBody, VarMap, O1), O1 = [_ | _], evalProg(T, O1, O), !.
evalProg([H | _], VarMap, O):- H = ifProgram(Cond, IfBody, _), evalExpr(Cond, VarMap, Value), Value =:= 1,
								evalProg(IfBody, VarMap, O1), integer(O1), O = O1, !.
evalProg([H | _], VarMap, O):- H = ifProgram(Cond, _, ElseBody), evalExpr(Cond, VarMap, Value), Value =:= 0,
								evalProg(ElseBody, VarMap, O1), O1 = error(X), O = error(X), !.
evalProg([H | T], VarMap, O):- H = ifProgram(Cond, _, ElseBody), evalExpr(Cond, VarMap, Value), Value =:= 0,
								evalProg(ElseBody, VarMap, O1), O1 = [_ | _], evalProg(T, O1, O), !.
evalProg([H | _], VarMap, O):- H = ifProgram(Cond, _, ElseBody), evalExpr(Cond, VarMap, Value), Value =:= 0,
								evalProg(ElseBody, VarMap, O1), integer(O1), O = O1, !.

evalProg([H | _], VarMap, O):- H = forProgram(Asgn, _, _, _), Asgn = asgn(var(_), Expr),
								evalExpr(Expr, VarMap, Value), Value = error('e'), O = error('e'), !.
evalProg([H | _], VarMap, O):- H = forProgram(Asgn, Cond, _, _), Asgn = asgn(var(Name), Expr),
								evalExpr(Expr, VarMap, Value), uniqueInsert(Name, Value, VarMap, [], NewMap),
								evalExpr(Cond, NewMap, IsTrue),
								IsTrue = error('e'), O = error('e'), !.
evalProg([H | T], VarMap, O):- H = forProgram(Asgn, Cond, _, _), Asgn = asgn(var(Name), Expr),
								evalExpr(Expr, VarMap, Value), uniqueInsert(Name, Value, VarMap, [], NewMap),
								evalExpr(Cond, NewMap, IsTrue),
								IsTrue =:= 0, evalProg(T, NewMap, O), !.
evalProg([H | _], VarMap, O):- H = forProgram(Asgn, Cond, _, _), Asgn = asgn(var(Name), Expr),
								evalExpr(Expr, VarMap, Value), uniqueInsert(Name, Value, VarMap, [], NewMap),
								evalExpr(Cond, NewMap, IsTrue), IsTrue =:= 1,
								evaluateForBody(H, NewMap, O1), O1 = error(X), O = error(X), !.
evalProg([H | _], VarMap, O):- H = forProgram(Asgn, Cond, _, _), Asgn = asgn(var(Name), Expr),
								evalExpr(Expr, VarMap, Value), uniqueInsert(Name, Value, VarMap, [], NewMap),
								evalExpr(Cond, 	NewMap, IsTrue), IsTrue =:= 1,
								evaluateForBody(H, NewMap, O1), integer(O1), O = O1, !.
evalProg([H | T], VarMap, O):- H = forProgram(Asgn, Cond, _, _), Asgn = asgn(var(Name), Expr),
								evalExpr(Expr, VarMap, Value), uniqueInsert(Name, Value, VarMap, [], NewMap),
 								evalExpr(Cond, NewMap, IsTrue), IsTrue =:= 1, 
								evaluateForBody(H, NewMap, O1), O1 = [_ | _], evalProg(T, O1, O), !.


%Predicate de evaluat body-ul unui Program de tip FOR

evaluateForBody(H, VarMap, R):- H = forProgram(_, _, _, ForBody),
								evalProg(ForBody, VarMap, R1), R1 = error(X), R = error(X), !.
evaluateForBody(H, VarMap, R):- H = forProgram(_, _, _, ForBody),
								evalProg(ForBody, VarMap, R1), integer(R1), R = R1, !.
evaluateForBody(H, VarMap, R):- H = forProgram(_, _, Increment, ForBody),
								evalProg(ForBody, VarMap, R1), R1 = [_ | _],
								Increment = asgn(var(_), Expr),
								evalExpr(Expr, R1, Value), Value = error('e'), R = error('e'), !.
evaluateForBody(H, VarMap, R):- H = forProgram(_, Cond, Increment, ForBody),
								evalProg(ForBody, VarMap, R1), R1 = [_ | _],
								Increment = asgn(var(Name), Expr), evalExpr(Expr, R1, Value),
								integer(Value), uniqueInsert(Name, Value, R1, [], NewMap),
								evalExpr(Cond, NewMap, IsTrue), IsTrue =:= 0, R = NewMap, !.
evaluateForBody(H, VarMap, R):- H = forProgram(_, Cond, Increment, ForBody),
								evalProg(ForBody, VarMap, R1), R1 = [_ | _],
								Increment = asgn(var(Name), Expr), evalExpr(Expr, R1, Value),
								integer(Value), uniqueInsert(Name, Value, R1, [], NewMap),
								evalExpr(Cond, NewMap, IsTrue), IsTrue =:= 1,
								evaluateForBody(H, [pair(Name, Value) | R1], R), !.


%PREDICATE FOLOSITE PENTRU PRODUCEREA REZULTATULUI

parseInputAux(L,R):- L1 = ['{' | L], append(L1, ['}'], R1), parseBody(R1, O, _), R = O, !.

parseInput(F,R):-read_file_to_string(F, S, []), lparse(S, L), parseInputAux(L, R1),
				evalProg(R1, [], O), ((O = error(X), R = X) ; (integer(O), R = O) ; (O = [_ | _], R = 'x')), !.
parseInput(F, R):- read_file_to_string(F, S, []), lparse(S, L), not(parseInputAux(L, _)), R = 'e', !.