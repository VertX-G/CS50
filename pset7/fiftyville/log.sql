-- Keep a log of any SQL queries you execute as you solve the mystery.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- find out what tables are available to figure out what kind of information is available
.tables
-- RESULT --
-- airports                  crime_scene_reports       people
-- atm_transactions          flights                   phone_calls
-- bank_accounts             interviews
-- courthouse_security_logs  passengers

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- a good place to start would be with the crime scene reports
.schema crime_scene_reports
-- to find out what types of information is available in the crime scene reports
-- RESULT --
-- CREATE TABLE crime_scene_reports (
--     id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     street TEXT,
--     description TEXT,
--     PRIMARY KEY(id)
-- );

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- list the crimes that took place on 28 July 2020 on Chamberlin Street
SELECT description FROM crime_scene_reports WHERE year = 2020 AND month = 7 AND day = 28 AND street LIKE "Chamberlin Street";
-- RESULT--
-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- find the interviews
.schema interviews
SELECT name, transcript FROM interviews WHERE year = 2020 AND month = 7 AND day = 28 and transcript LIKE "%courthouse%";
-- RESULT --
-- Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- get license plates for cars that left the courthouse between 10:15 and 10:25
-- Find out what type of information is available in the courthouse security logs
.schema courthouse_security_logs
-- RESULT --
-- CREATE TABLE courthouse_security_logs (
--     id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     hour INTEGER,
--     minute INTEGER,
--     activity TEXT,
--     license_plate TEXT,
--     PRIMARY KEY(id)
-- );
SELECT license_plate, hour, minute, activity FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25 AND activity LIKE "exit";
-- RESULT --
-- license_plate | hour | minute | activity
-- 5P2BI95 | 10 | 16 | exit
-- 94KL13X | 10 | 18 | exit
-- 6P58WS2 | 10 | 18 | exit
-- 4328GD8 | 10 | 19 | exit
-- G412CB7 | 10 | 20 | exit
-- L93JTIZ | 10 | 21 | exit
-- 322W7JE | 10 | 23 | exit
-- 0NTHK55 | 10 | 23 | exit

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- get atm transactions from fifer street for withdrawals on the morning of 28/07/2020 (before Eugene arrived at the courthouse)
.schema atm_transactions
-- RESULT--
-- CREATE TABLE atm_transactions (
--     id INTEGER,
--     account_number INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     atm_location TEXT,
--     transaction_type TEXT,
--     amount INTEGER,
--     PRIMARY KEY(id)
-- );
SELECT * FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location LIKE "Fifer Street" AND transaction_type LIKE "withdraw";
-- RESULT --
-- id | account_number | year | month | day | atm_location | transaction_type | amount
-- 246 | 28500762 | 2020 | 7 | 28 | Fifer Street | withdraw | 48
-- 264 | 28296815 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
-- 266 | 76054385 | 2020 | 7 | 28 | Fifer Street | withdraw | 60
-- 267 | 49610011 | 2020 | 7 | 28 | Fifer Street | withdraw | 50
-- 269 | 16153065 | 2020 | 7 | 28 | Fifer Street | withdraw | 80
-- 288 | 25506511 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
-- 313 | 81061156 | 2020 | 7 | 28 | Fifer Street | withdraw | 30
-- 336 | 26013199 | 2020 | 7 | 28 | Fifer Street | withdraw | 35

-- correlate atm transactions with bank accounts and people
.schema bank_accounts
-- RESULT --
-- CREATE TABLE bank_accounts (
--     account_number INTEGER,
--     person_id INTEGER,
--     creation_year INTEGER,
--     FOREIGN KEY(person_id) REFERENCES people(id)
-- );
SELECT * FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location LIKE "Fifer Street" AND transaction_type LIKE "withdraw");
-- RESULT --
-- account_number | person_id | creation_year
-- 49610011 | 686048 | 2010
-- 26013199 | 514354 | 2012
-- 16153065 | 458378 | 2012
-- 28296815 | 395717 | 2014
-- 25506511 | 396669 | 2014
-- 28500762 | 467400 | 2014
-- 76054385 | 449774 | 2015
-- 81061156 | 438727 | 2018

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- check call logs at around 10:15 for calls of less than a minute
.schema phone_calls
-- RESULT --
-- CREATE TABLE phone_calls (
--     id INTEGER,
--     caller TEXT,
--     receiver TEXT,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     duration INTEGER,
--     PRIMARY KEY(id)
-- );
SELECT * FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <60;
-- RESULT --
-- id | caller | receiver | year | month | day | duration
-- 221 | (130) 555-0289 | (996) 555-8899 | 2020 | 7 | 28 | 51
-- 224 | (499) 555-9472 | (892) 555-8872 | 2020 | 7 | 28 | 36
-- 233 | (367) 555-5533 | (375) 555-8161 | 2020 | 7 | 28 | 45
-- 251 | (499) 555-9472 | (717) 555-1342 | 2020 | 7 | 28 | 50
-- 254 | (286) 555-6063 | (676) 555-6554 | 2020 | 7 | 28 | 43
-- 255 | (770) 555-1861 | (725) 555-3243 | 2020 | 7 | 28 | 49
-- 261 | (031) 555-6622 | (910) 555-3251 | 2020 | 7 | 28 | 38
-- 279 | (826) 555-1652 | (066) 555-9701 | 2020 | 7 | 28 | 55
-- 281 | (338) 555-6650 | (704) 555-2131 | 2020 | 7 | 28 | 54

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- check earliest flight out of fiftyville on 29/07/2020 and see who bought tickets, cross reference with phonecalls
.schema airports
-- RESULT --
-- CREATE TABLE airports (
--     id INTEGER,
--     abbreviation TEXT,
--     full_name TEXT,
--     city TEXT,
--     PRIMARY KEY(id)
-- );
SELECT * FROM airports WHERE city LIKE "Fiftyville";
-- RESULT --
-- id | abbreviation | full_name | city
-- 8 | CSF | Fiftyville Regional Airport | Fiftyville

.schema flights
-- RESULT --
-- CREATE TABLE flights (
--     id INTEGER,
--     origin_airport_id INTEGER,
--     destination_airport_id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     hour INTEGER,
--     minute INTEGER,
--     PRIMARY KEY(id),
--     FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
--     FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
-- );

SELECT * FROM flights WHERE origin_airport_id IN (SELECT id FROM airports WHERE city LIKE "Fiftyville") AND year = 2020 AND month = 7 AND day = 28 ORDER BY ((hour * 100) + minute) LIMIT 1;
-- RESULT --
-- id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
-- 6 | 8 | 5 | 2020 | 7 | 28 | 13 | 49

-- get passenger manifest for that flight
.schema passengers
-- RESULT --
-- CREATE TABLE passengers (
--     flight_id INTEGER,
--     passport_number INTEGER,
--     seat TEXT,
--     FOREIGN KEY(flight_id) REFERENCES flights(id)
-- );

SELECT * FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE origin_airport_id IN (SELECT id FROM airports WHERE city LIKE "Fiftyville") AND year = 2020 AND month = 7 AND day = 28 ORDER BY ((hour * 100) + minute) LIMIT 1);
-- RESULT --
-- flight_id | passport_number | seat
-- 6 | 3835860232 | 9A
-- 6 | 1618186613 | 2C
-- 6 | 7179245843 | 3B
-- 6 | 1682575122 | 4B
-- 6 | 7597790505 | 5D
-- 6 | 6128131458 | 6B
-- 6 | 6264773605 | 7D
-- 6 | 3642612721 | 8A

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Find correlation from 'people' table between the courthouse security logs license plate, bank accounts, phone caller and flight passengers

.schema people
-- RESULT --
-- CREATE TABLE people (
--     id INTEGER,
--     name TEXT,
--     phone_number TEXT,
--     passport_number INTEGER,
--     license_plate TEXT,
--     PRIMARY KEY(id)
-- );

-- Licence plate owners
SELECT * FROM people
WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25 AND activity LIKE "exit");
-- RESULT --
-- id | name | phone_number | passport_number | license_plate
-- 221103 | Patrick | (725) 555-4692 | 2963008352 | 5P2BI95
-- 243696 | Amber | (301) 555-4174 | 7526138472 | 6P58WS2
-- 396669 | Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ
-- 398010 | Roger | (130) 555-0289 | 1695452385 | G412CB7
-- 467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
-- 514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
-- 560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55
-- 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X

-- ATM withdrawal bank account owners
SELECT * FROM people
WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location LIKE "Fifer Street" AND transaction_type LIKE "withdraw"));
-- RESULT --
-- id | name | phone_number | passport_number | license_plate
-- 395717 | Bobby | (826) 555-1652 | 9878712108 | 30G67EN
-- 396669 | Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ
-- 438727 | Victoria | (338) 555-6650 | 9586786673 | 8X428L0
-- 449774 | Madison | (286) 555-6063 | 1988161715 | 1106N58
-- 458378 | Roy | (122) 555-4581 | 4408372428 | QX4YZN3
-- 467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
-- 514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
-- 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X

-- phone call number owners
SELECT * FROM people
WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <60);
-- RESULT --
-- id | name | phone_number | passport_number | license_plate
-- 395717 | Bobby | (826) 555-1652 | 9878712108 | 30G67EN
-- 398010 | Roger | (130) 555-0289 | 1695452385 | G412CB7
-- 438727 | Victoria | (338) 555-6650 | 9586786673 | 8X428L0
-- 449774 | Madison | (286) 555-6063 | 1988161715 | 1106N58
-- 514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
-- 560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55
-- 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
-- 907148 | Kimberly | (031) 555-6622 | 9628244268 | Q12B3Z3

-- flight passengers
SELECT * FROM people
WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE origin_airport_id IN (SELECT id FROM airports WHERE city LIKE "Fiftyville") AND year = 2020 AND month = 7 AND day = 29 ORDER BY ((hour * 100) + minute) LIMIT 1));
-- RESULT --
-- id | name | phone_number | passport_number | license_plate
-- 395717 | Bobby | (826) 555-1652 | 9878712108 | 30G67EN
-- 398010 | Roger | (130) 555-0289 | 1695452385 | G412CB7
-- 449774 | Madison | (286) 555-6063 | 1988161715 | 1106N58
-- 467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
-- 560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55
-- 651714 | Edward | (328) 555-1152 | 1540955065 | 130LD9Z
-- 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
-- 953679 | Doris | (066) 555-9701 | 7214083635 | M51FA04

-- Putting it all together
SELECT * FROM people
WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25 AND activity LIKE "exit")
AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location LIKE "Fifer Street" AND transaction_type LIKE "withdraw"))
AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <60)
AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE origin_airport_id IN (SELECT id FROM airports WHERE city LIKE "Fiftyville") AND year = 2020 AND month = 7 AND day = 29 ORDER BY ((hour * 100) + minute) LIMIT 1));
-- RESULT --
-- The thief is:
-- id | name | phone_number | passport_number | license_plate
-- 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- find the destination of the flight
SELECT city FROM airports WHERE id IN (SELECT destination_airport_id FROM flights WHERE id IN (SELECT id FROM flights WHERE origin_airport_id IN (SELECT id FROM airports WHERE city LIKE "Fiftyville") AND year = 2020 AND month = 7 AND day = 29 ORDER BY ((hour * 100) + minute) LIMIT 1));
-- RESULT --
-- city
-- London

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- find the accomplace
SELECT name FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE caller IN (SELECT phone_number FROM people WHERE name LIKE "Ernest") AND year = 2020 AND month = 7 AND day = 28 AND duration <60);
-- RESULT --
-- name
-- Berthold