module Interpreter
  (
    -- * Types
    Prog,
    Asgn,

    -- * Functions
    evalRaw,
    evalAdt,
  ) where

-------------------------------------------------------------------------------
--------------------------------- The Expr ADT  -------------------------------
-------------------------------------------------------------------------------
data Expr = Add Expr Expr
          | Sub Expr Expr
          | Mult Expr Expr
          | Equal Expr Expr
          | Smaller Expr Expr
          | Symbol String
          | Value Int deriving (Show, Read)


{-Tipul dictionar de la laborator in care retin valorile varoabilelor,
echivalentul mapei de variabile de la tema din Java-}
type VariableMap a = [(String, a)]


{-Procedura care pe baza unuei mape de variabile si a numelui variabilei
determina valoarea acesteia si intoarce intr-un obiect de tip Either in functie
de valoarea gasita, mesaj de variabila nedeclarata daca s-a epuizat mapa de variabile
sau un valoarea-}
findVariableValue :: (VariableMap Int) -> String -> Either String Int
findVariableValue [] variableName = Left "Uninitialized variable"
findVariableValue (pair : pairs) variableName = if (fst pair) == variableName then (Right (snd pair)) else (findVariableValue pairs variableName)


{-Procedura care pe baza unei mape de variabile si o expresie produce evaluarea
expresiei si intoarce un obiect de tip Either in functie de rezultatul evaluarii, 
mesaj de variabila nedeclarata obtinut in urma evaluarii unei subexpresii a unei expresii,
acesta fiind rezultatul expresiei curente daca una din subexpresii contine variabile nedeclarate,
sau valoarea expresiei, folosind constructorul Right
Pentru evaluare analizez cazurile expresiei: adunare, scadere, inmultire, egalitate,
sau comparatie, folosind keyword-ul case
In evaluarea unei expresii singura eroare care poate fi intalnita este folosirea unei variabile neintializate,
astfel, daca in evaluarea unei expresii, evluarea subexpresiei acelei expresii produce o eroare, eraorea care va
rezulta din evaluarea expresiei mari va fi de variabila neinitializata-}
evaluateExpression :: (VariableMap Int) -> Expr -> Either String Int
evaluateExpression variableMap expression = case expression of
                                            Value number -> Right number
                                            Symbol variableName -> findVariableValue variableMap variableName
                                            Add leftSide rightSide -> case (evaluateExpression variableMap leftSide, evaluateExpression variableMap rightSide) of
                                                                      (Left error1, _) -> Left "Uninitialized variable"
                                                                      (_, Left error2) -> Left "Uninitialized variable"
                                                                      (Right result1, Right result2) -> Right (result1 + result2)
                                            Sub leftSide rightSide -> case (evaluateExpression variableMap leftSide, evaluateExpression variableMap rightSide) of
                                                                      (Left error1, _) -> Left "Uninitialized variable"
                                                                      (_, Left error2) -> Left "Uninitialized variable"
                                                                      (Right result1, Right result2) -> Right (result1 - result2)
                                            Mult leftSide rightSide -> case (evaluateExpression variableMap leftSide, evaluateExpression variableMap rightSide) of
                                                                      (Left error1, _) -> Left "Uninitialized variable"
                                                                      (_, Left error2) -> Left "Uninitialized variable"
                                                                      (Right result1, Right result2) -> Right (result1 * result2)
                                            Equal leftSide rightSide -> case (evaluateExpression variableMap leftSide, evaluateExpression variableMap rightSide) of
                                                                      (Left error1, _) -> Left "Uninitialized variable"
                                                                      (_, Left error2) -> Left "Uninitialized variable"
                                                                      (Right result1, Right result2) -> if result1 == result2 then Right 1
                                                                                                                              else Right (-1)
                                            Smaller leftSide rightSide -> case (evaluateExpression variableMap leftSide, evaluateExpression variableMap rightSide) of
                                                                      (Left error1, _) -> Left "Uninitialized variable"
                                                                      (_, Left error2) -> Left "Uninitialized variable"
                                                                      (Right result1, Right result2) -> if result1 < result2 then Right 1
                                                                                                                             else Right (-1)


-- TODO Implement a parser for the Expr ADT.
--
{-EVAL DE EXPR SA RETURNEZE UN EITHER STRING INT, IAR PT BOOLEAN: -1 = FALSE SI 1 = TRUE-}
-------------------------------------------------------------------------------
---------------------------------- The Prog ADT -------------------------------
-------------------------------------------------------------------------------
data Asgn = Asgn String Expr deriving (Show, Read)

data Prog = Eq Asgn
          | Seq Prog Prog
          | If Expr Prog Prog
          | For Asgn Expr Asgn Prog
          | Assert Expr
          | Return Expr deriving (Show, Read)


{-Procedura care primeste o mapa de variabile si un program si evalueaza programul, returnand
o eroare, o valoare, sau o mapa noua de variabile, daca in acel program am asignari de variabile.
Aceasta procedura am folsit-o la evaluarea corpului unui program de tip For, deoarece trebuie
sa evaluez la fiecare expresia, programul si asignment-ul 2, modul in care lucreaza o expresie de tip
for in mod normal, iar acest lucru ar fi fost destul de dificil in functia in care am realizat evaluarea
celorlalte tipuri de programe.
Pentru evaluarea corpului unui program de tip For incep prin a evalua expresia, iar daca acea evaluare
nu produce eroare, ci produce valaorea 1, adica program corect, evaluez programul din for, iar daca acesta
produce eroare propag eroarea, daca produce o valoare, atunci s-a dat de un return si propag acel rezultat, el
fiind rezultatul programului. Daca evaluarea corpului mi-a returnat o noua mapa de variabile, atunci trec la
evaluarea asignment-ului 2, iar daca acesta produce eroare propag eroarea catre programele superioare, altfel
se intoarce o mapa de variabile modificata si reevaluez corpul For-ului prin reapelarea acestei proceduri.

OBSERVATIE: APELEZ ACEAST PROCEDURA DUPA CE MA ASIGUR CA EVLUAREA ASIGNEMT-ULUI 1 NU PRODUCE EROARE ( FAC ACEST
LUCRU IN FUNCTIA IN CARE EVALUEZ TOATE PROGRAMELE)-}
evaluateForBody :: (VariableMap Int) -> Prog -> Either (Either String Int) (VariableMap Int)
evaluateForBody variableMap (For asignment1 expression asignment2 program) = case (evaluateExpression variableMap expression) of
                  Left error -> Left (Left error)
                  Right value -> if value == 1 then
                              case (evaluateProgram variableMap program) of
                              Left (Left error) -> Left (Left error)
                              Left (Right value) -> Left (Right value)
                              Right updatedVariableMap -> case (evaluateProgram updatedVariableMap (Eq asignment2)) of
                                                       Left (Left error) -> Left (Left error)
                                                       Right updatedVariableMap -> evaluateForBody updatedVariableMap (For asignment1 expression asignment2 program)
                              else (Right variableMap)           


{-Procedura care insereaza unic in mapa de variabile o noua pereche (String, Int) care reprezinta noua
valoare a variabilei. Prin acest lucru asigur ca lista de perechi ce contine valorile tuturor variabilelor
la un moment dat nu va avea foarte multe elemente, astfel mentinandu-i dimensiunea la numarul de variabile intalnite
pana la acel moment in program
In caz ca lista e vida atunci inserez simplu perechea, altfel vad inceputul listei daca are numele acelei variabile,
iar daca il are returnez lista ce are noul inceput perechea de inserat, altfel inserez inceputul listei in rezultatul
inserarii perechii in lista-}
uniqueInsert :: (VariableMap Int) -> (String, Int) -> (VariableMap Int)
uniqueInsert [] (name, value) = [(name, value)]
uniqueInsert (pair : pairs) (name, value) = if (fst pair) == name then ((name, value) : pairs)
                                                                  else (pair : (uniqueInsert pairs (name, value)))


{-Procedura care primeste ca parametri o mapa de variabile si un program si il evalueaza producand
ca rezultat un obiect de tip Either care contine fie un obiecte de tip Either ce contine mesaj de eroare,
daca program nu are un return statement sau daca se foloseste o variabila nedeclarata sau o valoare, daca
in program se intalneste un return statement, sau un obiect de tip Either ce contine o noua mapa de variabile
in caz ca cea veche se updateaza, se intalnesc programe de asignare.
La analiza programelor, daca un subprogram produce eroare, atunci acea eroare va fi si rezultatul evaluarii
programului curent, nemaievaluand programul in continuare
Pentru evaluare folosesc keyword-ul case pentru a analiza structura unui program ce urmeaza a fi analizat, dar si
pentru a vedea rezultatul evaluarii unui program, deoarece nu are sens sa evaluez restul programului daca in momentul
curent analiza unui program duce la eroare-}
evaluateProgram :: (VariableMap Int) -> Prog -> Either (Either String Int) (VariableMap Int)
evaluateProgram variableMap program = case program of
                    Eq (Asgn variableName expression) -> case (evaluateExpression variableMap expression) of
                                                      Left error -> Left (Left error)
                                                      Right value -> Right (uniqueInsert variableMap (variableName, value))
                                                      
                    Seq firstPart secondPart -> case (evaluateProgram variableMap firstPart) of
                                            Left (Left error) -> Left (Left error)
                                            Left (Right returnValue) -> Left (Right returnValue)
                                            Right updatedVariableMap -> evaluateProgram updatedVariableMap secondPart
                    If condition ifBody elseBody -> case condition of
                                                Equal leftSide rightSide -> case (evaluateExpression variableMap leftSide, evaluateExpression variableMap rightSide) of
                                                                        (Left error1, _) -> Left (Left error1)
                                                                        (_, Left error2) -> Left (Left error2)
                                                                        (Right result1, Right result2) -> if result1 == result2
                                                                                                      then evaluateProgram variableMap ifBody
                                                                                                      else evaluateProgram variableMap elseBody
                                                Smaller leftSide rightSide -> case (evaluateExpression variableMap leftSide, evaluateExpression variableMap rightSide) of
                                                                          (Left error1, _) -> Left (Left error1)
                                                                          (_, Left error2) -> Left (Left error2)
                                                                          (Right result1, Right result2) -> if result1 < result2
                                                                                                        then evaluateProgram variableMap ifBody
                                                                                                        else evaluateProgram variableMap elseBody
                    
                    For asignment1 expression asignment2 program -> case (evaluateProgram variableMap (Eq asignment1)) of
                                                                 Left (Left error) -> Left (Left error)
                                                                 Right updatedVariableMap -> evaluateForBody updatedVariableMap (For asignment1 expression asignment2 program)
                                                              
                    Assert expression -> case (evaluateExpression variableMap expression) of
                                      Left error -> Left (Left error)
                                      Right value -> if value == 1 then Right variableMap else (Left (Left "Assert failed"))
                                      
                    Return expression -> case (evaluateExpression variableMap expression) of
                                         Left error -> Left (Left error)
                                         Right value -> Left (Right value)


-- TODO Implement a parser for the Prog ADT.
--

-- TODO The *parse* function. It receives a String - the program in
-- a "raw" format and it could return *Just* a program as an instance of the
-- *Prog* data type if no parsing errors are encountered, or Nothing if parsing
-- failed.
--
-- This is composed with evalAdt to yield the evalRaw function.
parse :: String -> Maybe Prog
parse s = undefined

-------------------------------------------------------------------------------
-------------------------------- The Interpreter ------------------------------
-------------------------------------------------------------------------------

-- TODO The *evalAdt* function.  It receives the program as an instance of the
-- *Prog* data type and returns an instance of *Either String Int*; that is,
-- the result of interpreting the program.
--
-- The result of a correct program is always an Int.  This is a simplification
-- we make in order to ease the implementation.  However, we wrap this Int with
-- a *Either String* type constructor to handle errors.  The *Either* type
-- constructor is defined as:
--
-- data Either a b = Left a | Right b
--
-- and it is generally used for error handling.  That means that a value of
-- *Left a* - Left String in our case - wraps an error while a value of *Right
-- b* - Right Int in our case - wraps a correct result (notice that Right is a
-- synonym for "correct" in English).
-- 
-- For further information on Either, see the references in the statement of
-- the assignment.
--


{-Procedura din scheletul de cod din care apelez procedura implementata de mine
pentru evaluarea unui program plecand de la acel program si mapa de variabile goala.
In aceasta procedura pur si simplu ma uit la rezultatul pe care il produce procedura mea
in urma evluarii programului.
Daca aceasta evaluare imi intoarce o mapa de variabile, atunci clar in timpul evluarii
nu s-a intalnit un return, iar daca intoarce o eroare sau valoare, atunci rezultatul
este chiar eroarea, respectiv valoarea-}
evalAdt :: Prog -> Either String Int
evalAdt program = case (evaluateProgram [] program) of
                  Right variableMap -> Left "Missing return"
                  Left (Left error) -> Left error
                  Left (Right value) -> Right value


-- The *evalRaw* function is already implemented, but it relies on the *parse*
-- function which you have to implement.
--
-- Of couse, you can change this definition.  Only its name and type are
-- important.
evalRaw :: String -> Either String Int
evalRaw rawProg =
    case parse rawProg of
        Just prog -> evalAdt prog
        Nothing   -> Left "Syntax error"