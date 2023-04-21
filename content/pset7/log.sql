-- Keep a log of any SQL queries you execute as you solve the mystery.

/*
data do roubo: 28 de julho de 2020
local do roubo: Chamberlin Street

resolver:
1. Quem é o ladrão;
2. Para qual cidade ele fugiu;
3. Quem é o cúmplice
*/

-- query 1: filtrando a descrição pela data do evento
SELECT description
FROM crime_scene_reports
WHERE day = 28
AND month = 7
AND year = 2020
AND street = "Chamberlin Street";
    /* output: Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
    Interviews were conducted today with three witnesses who were present at the time — each of
    their interview transcripts mentions the courthouse. */

-- filtrando todas as testemunhas que citaram "courthouse" em seus relatos
SELECT name, transcript
FROM interviews
WHERE day = 28
AND month = 7
AND year = 2020
AND transcript = "%courthouse%";
    /* TESTEMUNHA 1 (RUTH): "I don't know the thief's name, but it was
    someone I recognized. Earlier this morning, before I arrived at the
    courthouse, I was walking by the ATM on Fifer Street and saw the thief
    there withdrawing some money." */

    /* TESTEMUNHA 2 (EUGENE): "Sometime within ten minutes of the theft,
    I saw the thief get into a car in the courthouse parking lot and
    drive away.If you have security footage from the courthouse parking lot,
    you might want to look for cars that left the parking lot in that time frame." */

    /* TESTEMUNHA 3 (RAYMOND): "As the thief was leaving the courthouse,
    they called someone who talked to them for less than a minute.
    In the call, I heard the thief say that they were planning to
    take the earliest flight out of Fiftyville tomorrow. The thief
    then asked the person on the other end of the phone to purchase the flight ticket." */

-- informações do testemunho 1: movimentações de contas bancárias na Fifer Street
SELECT name
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE year = 2020
AND month = 7
AND day = 28
AND atm_location = "Fifer Street"
AND transaction_type = "withdraw"
ORDER BY name;
    -- suspeitos: Bobby, Danielle, Elizabeth, Ernest, Madison, Roy, Russell, Victoria

-- testemunho 2: filtrando as placas dos carros que saíram do estacionamento da corte
SELECT name
FROM people
JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate
WHERE year = 2020
AND month = 7
AND day = 28
AND hour = 10
AND minute > 15
AND minute <= 25
AND activity = "exit"
ORDER BY name;
    -- suspeitos: Amber, Danielle, Elizabeth, Ernest, Evelyn, Patrick, Roger, Russell
    
    /* PRINCIPAIS SUSPEITOS: Danielle, Elizabeth, Ernest, Russell */

-- testemunho 3: filtrando os registros da ligações
SELECT name
FROM people
WHERE phone_number IN (SELECT caller
  FROM phone_calls
  WHERE year = 2020
  AND month = 7
  AND day = 28
  AND duration < 60)
  ORDER BY name;
    -- suspeitos: Bobby, Ernest, Evelyn, Kimberly, Madison, Roger, Russuel, Victoria

-- Retorna o horário do primeiro voo que saiu de Fiftyville no dia após o roubo
SELECT hour, minute
FROM flights
WHERE year = 2020
AND month = 7
AND day = 29
AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville")
ORDER BY hour, minute
LIMIT 1;
    -- horário: 8h20min
    
-- filtrando os passageiros que pegaram o voo do horário fornecido acima
SELECT hour, minute
FROM flights
WHERE year = 2020
AND month = 7
AND day = 29
AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville")
ORDER BY hour, minute
LIMIT 1;
    -- suspeitos: Bobby, Danielle, Doris, Edward, Ernest, Evelyn, Madison, Roger (ERNEST É O PRINCIPAL SUSPEITO)
    
-- encontrando o destinatário da ligação de Ernest
SELECT name
FROM people
WHERE phone_number IN (SELECT receiver
FROM phone_calls
WHERE year = 2020
AND month = 7
AND day = 28
AND duration < 60
AND caller IN(SELECT phone_number
FROM people
WHERE name = "Ernest"));
    -- cúmplice: Berthold
    
-- filtrando o destino do voo 
SELECT name
FROM people
WHERE phone_number IN (SELECT receiver
FROM phone_calls
WHERE year = 2020
AND month = 7
AND day = 28
AND duration < 60
AND caller IN(SELECT phone_number
FROM people
WHERE name = "Ernest"));
    -- destino: London
    
    