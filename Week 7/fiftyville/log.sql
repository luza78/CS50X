-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Look at tables in db
.tables

--What's in crimescene tables ?
.schema crime_scene_reports

-- Lets get the report from day + month + street of crime
SELECT description FROM crime_scene_reports WHERE day = 28 AND month = 7 AND street LIKE 'Humphrey%';


-- cs50 duck was stolen 10:15am at Humphrey street bakery. 3 interviews conducted on the same day, all mention bakery
-- Let's see if we can find those interviews
.schema interviews

--Interviews were same and and mention bakery
-- I wanted the year for the crime to make sure i get the right interviews (2021)
SELECT description, year FROM crime_scene_reports WHERE day = 28 AND month = 7 AND street LIKE 'Humphrey%';

--find interviews
 SELECT transcript FROM interviews where day = 28 AND month = 7 AND year = 2021 AND transcript LIKE '%bakery%';

 --within 10 minutes thief got into the car CHECK security footage for cars leaving the parking.
 --Thief was withdrawing money from ATM at Leggett Street
 --| As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
 -- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
 -- The thief then asked the person on the other end of the phone to purchase the flight ticket.

 -- Lets follow the lead with the car from bakery security logs
 .schema bakery_security_logs
 SELECT * from bakery_security_logs WHERE year = 2021 AND month = 07 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;

 --plates from bakery
 +-----+------+-------+-----+------+--------+----------+---------------+
| id  | year | month | day | hour | minute | activity | license_plate |
+-----+------+-------+-----+------+--------+----------+---------------+
| 260 | 2021 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
| 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
| 262 | 2021 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
| 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
| 264 | 2021 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
| 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
| 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
| 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
+-----+------+-------+-----+------+--------+----------+---------------+

-- lets see who withdrew money from ATM at leggert st
.schema atm_transactions
SELECT * FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE 'legget%';

+-----+----------------+------+-------+-----+----------------+------------------+--------+
| id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     |
| 264 | 28296815       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     |
| 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
| 269 | 16153065       | 2021 | 7     | 28  | Leggett Street | withdraw         | 80     |
| 275 | 86363979       | 2021 | 7     | 28  | Leggett Street | deposit          | 10     |
| 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 313 | 81061156       | 2021 | 7     | 28  | Leggett Street | withdraw         | 30     |
| 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     |
+-----+----------------+------+-------+-----+----------------+------------------+--------+

--Lets check the phone records
SELECT * FROM phone_calls WHERE year = 2021 AND month = 07 AND day = 28;

-- duration less than a minute
SELECT * FROM phone_calls WHERE year = 2021 AND month = 07 AND day = 28 AND duration < 60;

+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 221 | (130) 555-0289 | (996) 555-8899 | 2021 | 7     | 28  | 51       |
| 224 | (499) 555-9472 | (892) 555-8872 | 2021 | 7     | 28  | 36       |
| 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
| 251 | (499) 555-9472 | (717) 555-1342 | 2021 | 7     | 28  | 50       |
| 254 | (286) 555-6063 | (676) 555-6554 | 2021 | 7     | 28  | 43       |
| 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       |
| 261 | (031) 555-6622 | (910) 555-3251 | 2021 | 7     | 28  | 38       |
| 279 | (826) 555-1652 | (066) 555-9701 | 2021 | 7     | 28  | 55       |
| 281 | (338) 555-6650 | (704) 555-2131 | 2021 | 7     | 28  | 54       |
+-----+----------------+----------------+------+-------+-----+----------+

--Let's comebine some queries and see if we can find a match....
SELECT * FROM people WHERE license_plate IN(
SELECT license_plate from bakery_security_logs
WHERE year = 2021 AND month = 07
AND day = 28 AND hour = 10
AND minute >= 15 AND minute <= 25)
AND phone_number IN
(SELECT caller FROM phone_calls
WHERE year = 2021 AND month = 07
AND day = 28 AND duration < 60);

+--------+--------+----------------+-----------------+---------------+
|   id   |  name  |  phone_number  | passport_number | license_plate |
+--------+--------+----------------+-----------------+---------------+
| 398010 | Sofia  | (130) 555-0289 | 1695452385      | G412CB7       |
| 514354 | Diana  | (770) 555-1861 | 3592750733      | 322W7JE       |
| 560886 | Kelsey | (499) 555-9472 | 8294398571      | 0NTHK55       |
| 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+--------+----------------+-----------------+---------------+

--
--Let's see if any of them made an atm transaction.....
SELECT name FROM people WHERE id IN
(SELECT person_id FROM bank_accounts
WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE 'legget%'));

-- Diana and Bruce

--lets find out more about Diana and Bruce
.schema people

--Let's find out if they are on any flights
SELECT flight_id FROM passengers
WHERE passport_number IN
(SELECT passport_number FROM people where name = 'Bruce' OR name = 'Diana')

--I got a flight ID returned for Bruce 36, lets find out if it's Bruce or Diana
+-----------+
| flight_id |
+-----------+
| 18        |
| 24        |
| 36        |
| 54        |
+-----------+

-- Le'ts see where these flights are to
 SELECT * FROM flights WHERE id = 18 OR id = 24 OR id = 36 OR id = 54;

+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      |
| 24 | 7                 | 8                      | 2021 | 7     | 30  | 16   | 27     |
| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |
| 54 | 8                 | 5                      | 2021 | 7     | 30  | 10   | 19     |
+----+-------------------+------------------------+------+-------+-----+------+--------+

--Let's see where the origins are
SELECT * FROM airports WHERE id = 7 OR id = 8;


+----+--------------+-----------------------------+------------+
| id | abbreviation |          full_name          |    city    |
+----+--------------+-----------------------------+------------+
| 7  | DXB          | Dubai International Airport | Dubai      |
| 8  | CSF          | Fiftyville Regional Airport | Fiftyville |
+----+--------------+-----------------------------+------------+

-- The other flights destinations
+----+--------------+-----------------------------------------+---------------+
| id | abbreviation |                full_name                |     city      |
+----+--------------+-----------------------------------------+---------------+
| 4  | LGA          | LaGuardia Airport                       | New York City |
| 5  | DFS          | Dallas/Fort Worth International Airport | Dallas        |
| 6  | BOS          | Logan International Airport             | Boston        |
+----+--------------+-----------------------------------------+---------------+

--Bruce goes to Laguardia / Diana others


-- Let's figure out who the thief called
SELECT * FROM people WHERE phone_number IN
(SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 07 AND day = 28 AND duration < 60 AND caller IN
(SELECT phone_number FROM people WHERE name = 'Bruce' OR name = 'Diana'));

+--------+--------+----------------+-----------------+---------------+
|   id   |  name  |  phone_number  | passport_number | license_plate |
+--------+--------+----------------+-----------------+---------------+
| 847116 | Philip | (725) 555-3243 | 3391710505      | GW362R6       |
| 864400 | Robin  | (375) 555-8161 | NULL            | 4V16VO0       |
+--------+--------+----------------+-----------------+---------------+

SELECT * FROM passengers WHERE passport_number = 3391710505;

+-----------+-----------------+------+
| flight_id | passport_number | seat |
+-----------+-----------------+------+
| 10        | 3391710505      | 2A   |
| 28        | 3391710505      | 2A   |
| 47        | 3391710505      | 4D   |
+-----------+-----------------+------+

--Lets see where the flights origin and destination is
SELECT * FROM flights WHERE id in
(SELECT flight_id FROM passengers WHERE passport_number = 3391710505);

+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 10 | 8                 | 4                      | 2021 | 7     | 30  | 13   | 55     |
| 28 | 3                 | 8                      | 2021 | 7     | 26  | 22   | 49     |
| 47 | 4                 | 8                      | 2021 | 7     | 30  | 9    | 46     |
+----+-------------------+------------------------+------+-------+-----+------+--------+
+----+--------------+-----------------------------------+---------------+
| id | abbreviation |             full_name             |     city      |
+----+--------------+-----------------------------------+---------------+
| 3  | LAX          | Los Angeles International Airport | Los Angeles   |
| 4  | LGA          | LaGuardia Airport                 | New York City |
| 8  | CSF          | Fiftyville Regional Airport       | Fiftyville    |
+----+--------------+-----------------------------------+---------------+

-- Not him....

-- Who did bruce call
SELECT * FROM people WHERE phone_number IN
   ...> (SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 07 AND day = 28 AND duration < 60 AND caller IN
   ...> (SELECT phone_number FROM people WHERE name = 'Bruce'));
   +--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 864400 | Robin | (375) 555-8161 | NULL            | 4V16VO0       |
+--------+-------+----------------+-----------------+---------------+

SELECT * FROM bakery_security_logs WHERE license_plate = '4V16VO0';
+-----+------+-------+-----+------+--------+----------+---------------+
| id  | year | month | day | hour | minute | activity | license_plate |
+-----+------+-------+-----+------+--------+----------+---------------+
| 248 | 2021 | 7     | 28  | 8    | 50     | entrance | 4V16VO0       |
| 249 | 2021 | 7     | 28  | 8    | 50     | exit     | 4V16VO0       |
+-----+------+-------+-----+------+--------+----------+---------------+


--Robin drove past the bakery on the morning of the crime... SUS