-- Keep a log of any SQL queries you execute as you solve the mystery.

-- 000 -> Get the description of the crime
SELECT description
   ...> FROM crime_scene_reports
   ...> WHERE month = 7 AND day = 28 AND year = 2021
   ...> AND street = 'Humphrey Street';

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
-- Littering took place at 16:36. No known witnesses.

-- 001 -> Get id of crime
SELECT id
   ...> FROM crime_scene_reports
   ...> WHERE month = 7 AND day = 28 AND year = 2021
   ...> AND street = 'Humphrey Street';
-- Two ids: 295, 297

-- 002 -> Check Interviews OF  month = 7 AND day = 28 AND year = 2021 that mention bakery
SELECT transcript
   ...> FROM interviews
   ...> WHERE month = 7 AND day = 28 AND year = 2021
   ...> AND transcript LIKE '%bakery%';

-- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
-- I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- 003 check bakery_security_logs, car left within 10 minutes with car
SELECT activity, license_plate, hour, minute
   ...> FROM bakery_security_logs
   ...> WHERE month = 7 AND day = 28 AND year = 2021;
+----------+---------------+------+--------+
| activity | license_plate | hour | minute |
+----------+---------------+------+--------+
| entrance | 1M92998       | 8    | 2      |
| entrance | N507616       | 8    | 2      |
| exit     | 1M92998       | 8    | 2      |
| exit     | N507616       | 8    | 2      |
| entrance | 7Z8B130       | 8    | 7      |
| exit     | 7Z8B130       | 8    | 7      |
| entrance | 47MEFVA       | 8    | 13     |
| exit     | 47MEFVA       | 8    | 13     |
| entrance | D965M59       | 8    | 15     |
| entrance | HW0488P       | 8    | 15     |
| exit     | D965M59       | 8    | 15     |
| exit     | HW0488P       | 8    | 15     |
| entrance | L93JTIZ       | 8    | 18     |
| entrance | 94KL13X       | 8    | 23     |
| entrance | L68E5I0       | 8    | 25     |
| entrance | HOD8639       | 8    | 25     |
| exit     | HOD8639       | 8    | 25     |
| exit     | L68E5I0       | 8    | 34     |
| entrance | 1106N58       | 8    | 34     |
| entrance | W2CT78U       | 8    | 34     |
| exit     | W2CT78U       | 8    | 34     |
| entrance | 322W7JE       | 8    | 36     |
| entrance | 3933NUH       | 8    | 38     |
| exit     | 3933NUH       | 8    | 38     |
| entrance | 0NTHK55       | 8    | 42     |
| entrance | 1FBL6TH       | 8    | 44     |
| exit     | 1FBL6TH       | 8    | 44     |
| entrance | P14PE2Q       | 8    | 49     |
| exit     | P14PE2Q       | 8    | 49     |
| entrance | 4V16VO0       | 8    | 50     |
| exit     | 4V16VO0       | 8    | 50     |
| entrance | 8LLB02B       | 8    | 57     |
| exit     | 8LLB02B       | 8    | 57     |
| entrance | O784M2U       | 8    | 59     |
| exit     | O784M2U       | 8    | 59     |
| entrance | 4328GD8       | 9    | 14     |
| entrance | 5P2BI95       | 9    | 15     |
| entrance | 6P58WS2       | 9    | 20     |
| entrance | G412CB7       | 9    | 28     |
| entrance | R3G7486       | 10   | 8      |
| entrance | 13FNH73       | 10   | 14     |
| exit     | 5P2BI95       | 10   | 16     |
| exit     | 94KL13X       | 10   | 18     |
| exit     | 6P58WS2       | 10   | 18     |
| exit     | 4328GD8       | 10   | 19     |
| exit     | G412CB7       | 10   | 20     |
| exit     | L93JTIZ       | 10   | 21     |
| exit     | 322W7JE       | 10   | 23     |
| exit     | 0NTHK55       | 10   | 23     |
| exit     | 1106N58       | 10   | 35     |
| entrance | NRYN856       | 10   | 42     |
| entrance | WD5M8I6       | 10   | 44     |
| entrance | V47T75I       | 10   | 55     |
| entrance | 4963D92       | 11   | 6      |
| entrance | C194752       | 11   | 13     |
| entrance | 94MV71O       | 11   | 52     |
| entrance | FLFN3W0       | 12   | 20     |
| entrance | 207W38T       | 12   | 49     |
| entrance | RS7I6A0       | 13   | 8      |
| entrance | 4468KVT       | 13   | 30     |
| entrance | NAW9653       | 13   | 42     |
| exit     | NAW9653       | 14   | 18     |
| exit     | RS7I6A0       | 15   | 6      |
| exit     | 94MV71O       | 15   | 16     |
| exit     | WD5M8I6       | 16   | 6      |
| exit     | 4468KVT       | 16   | 38     |
| exit     | 207W38T       | 16   | 42     |
| exit     | C194752       | 16   | 47     |
| exit     | NRYN856       | 17   | 11     |
| exit     | 13FNH73       | 17   | 15     |
| exit     | V47T75I       | 17   | 16     |
| exit     | R3G7486       | 17   | 18     |
| exit     | FLFN3W0       | 17   | 36     |
| exit     | 4963D92       | 17   | 47     |
+----------+---------------+------+--------+

-- 004 check atm_transactions  as thief withrdrew money beforehand
SELECT atm_location, transaction_type, amount, account_number
   ...> FROM atm_transactions
   ...> WHERE month = 7 AND day = 28 AND year = 2021;

-- 004.0 Get all withdrawals of the day at Leggett Street
SELECT atm_location, transaction_type, amount, account_number
   ...> FROM atm_transactions
   ...> WHERE month = 7 AND day = 28 AND year = 2021
   ...> AND atm_location = 'Leggett Street';
+----------------+------------------+--------+----------------+
|  atm_location  | transaction_type | amount | account_number |
+----------------+------------------+--------+----------------+
| Leggett Street | withdraw         | 48     | 28500762       |
| Leggett Street | withdraw         | 20     | 28296815       |
| Leggett Street | withdraw         | 60     | 76054385       |
| Leggett Street | withdraw         | 50     | 49610011       |
| Leggett Street | withdraw         | 80     | 16153065       |
| Leggett Street | deposit          | 10     | 86363979       |
| Leggett Street | withdraw         | 20     | 25506511       |
| Leggett Street | withdraw         | 30     | 81061156       |
| Leggett Street | withdraw         | 35     | 26013199       |
+----------------+------------------+--------+----------------+

-- 005 check phone call for call shortly after theft that took less than 1 minute
SELECT caller, receiver
   ...> FROM phone_calls
   ...> WHERE month = 7 AND day = 28 AND year = 2021
   ...> AND duration <= 60
+----------------+----------------+
|     caller     |    receiver    |
+----------------+----------------+
| (130) 555-0289 | (996) 555-8899 |
| (499) 555-9472 | (892) 555-8872 |
| (367) 555-5533 | (375) 555-8161 |
| (609) 555-5876 | (389) 555-5198 |
| (499) 555-9472 | (717) 555-1342 |
| (286) 555-6063 | (676) 555-6554 |
| (770) 555-1861 | (725) 555-3243 |
| (031) 555-6622 | (910) 555-3251 |
| (826) 555-1652 | (066) 555-9701 |
| (338) 555-6650 | (704) 555-2131 |
+----------------+----------------+

-- 006 check flights of month = 7 AND day = 29 AND year = 2021 -> get earliest flight

-- 006.0 Get name of Fyftyville airport
SELECT *
   ...> FROM airports
   ...> WHERE city = 'Fiftyville';
+----+--------------+-----------------------------+------------+
| id | abbreviation |          full_name          |    city    |
+----+--------------+-----------------------------+------------+
| 8  | CSF          | Fiftyville Regional Airport | Fiftyville |

-- 006.1 Get earliest flight of next day in fiftyville
SELECT *
   ...> FROM flights
   ...> WHERE month = 7 AND day = 29 AND year = 2021;
+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      |
| 23 | 8                 | 11                     | 2021 | 7     | 29  | 12   | 15     |
| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |
| 43 | 8                 | 1                      | 2021 | 7     | 29  | 9    | 30     |
| 53 | 8                 | 9                      | 2021 | 7     | 29  | 15   | 20     |
+----+-------------------+------------------------+------+-------+-----+------+--------+

--  36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20

-- 007 Get passenger list of flight 36
SELECT *
   ...> from passengers
   ...> WHERE flight_id = 36;
+-----------+-----------------+------+
| flight_id | passport_number | seat |
+-----------+-----------------+------+
| 36        | 7214083635      | 2A   |
| 36        | 1695452385      | 3B   |
| 36        | 5773159633      | 4A   |
| 36        | 1540955065      | 5C   |
| 36        | 8294398571      | 6C   |
| 36        | 1988161715      | 6D   |
| 36        | 9878712108      | 7A   |
| 36        | 8496433585      | 7B   |
+-----------+-----------------+------+

-- 008 get info of all passengers
SELECT license_plate
FROM people
WHERE passport_number IN
(SELECT passport_number from passengers WHERE flight_id = 36);

+--------+--------+----------------+-----------------+---------------+
|   id   |  name  |  phone_number  | passport_number | license_plate |
+--------+--------+----------------+-----------------+---------------+
| 395717 | Kenny  | (826) 555-1652 | 9878712108      | 30G67EN       |
| 398010 | Sofia  | (130) 555-0289 | 1695452385      | G412CB7       |
| 449774 | Taylor | (286) 555-6063 | 1988161715      | 1106N58       |
| 467400 | Luca   | (389) 555-5198 | 8496433585      | 4328GD8       |
| 560886 | Kelsey | (499) 555-9472 | 8294398571      | 0NTHK55       |
| 651714 | Edward | (328) 555-1152 | 1540955065      | 130LD9Z       |
| 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
| 953679 | Doris  | (066) 555-9701 | 7214083635      | M51FA04       |
+--------+--------+----------------+-----------------+---------------+

-- 009 check which person was at bakery using license_plate

SELECT activity, license_plate, hour, minute
   FROM bakery_security_logs
   WHERE month = 7 AND day = 28 AND year = 2021
   AND license_plate IN
   (SELECT license_plate FROM people WHERE passport_number IN
   (SELECT passport_number from passengers WHERE flight_id = 36));

+----------+---------------+------+--------+
| activity | license_plate | hour | minute |
+----------+---------------+------+--------+
| entrance | 94KL13X       | 8    | 23     |
| entrance | 1106N58       | 8    | 34     |
| entrance | 0NTHK55       | 8    | 42     |
| entrance | 4328GD8       | 9    | 14     |
| entrance | G412CB7       | 9    | 28     |
| exit     | 94KL13X       | 10   | 18     |
| exit     | 4328GD8       | 10   | 19     |
| exit     | G412CB7       | 10   | 20     |
| exit     | 0NTHK55       | 10   | 23     |
| exit     | 1106N58       | 10   | 35     |
+----------+---------------+------+--------+

SELECT name FROM people
    JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
    WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND minute > 15 AND minute < 25
    AND people.license_plate IN
    (SELECT license_plate FROM people WHERE passport_number IN
    (SELECT passport_number from passengers WHERE flight_id = 36));

-- Names that where at bakery:
+--------+
|  name  |
+--------+
| Bruce  |
| Luca   |
| Sofia  |
| Kelsey |
+--------+

-- 010 Names of people who had phone calls less than 1 minute on day in question
SELECT name
   ...> FROM people JOIN phone_calls ON people.phone_number = phone_calls.caller
   ...> WHERE month = 7 AND day = 28 AND year = 2021
   ...> AND duration < 60;
+---------+
|  name   |
+---------+
| Sofia   |
| Kelsey  |
| Bruce   |
| Kelsey  |
| Taylor  |
| Diana   |
| Carina  |
| Kenny   |
| Benista |

-- 011 Find names of people who withdrew money at street
+---------+
|  name   |
+---------+
| Bruce   |
| Diana   |
| Brooke  |
| Kenny   |
| Iman    |
| Luca    |
| Taylor  |
| Benista |
+---------+

-- SUSPECT LIST: 10:15am was the theft
+--------+--------+----------------+-----------------+---------------+
|   id   |  name  |  phone_number  | passport_number | license_plate |
+--------+--------+----------------+-----------------+---------------+
| 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+--------+----------------+-----------------+---------------

--> Bruce was the thief!!!!

-- 012 get destination airport (ID: 4)
SELECT city
   ...> FROM airports
   ...> WHERE id = 4;

--> Going to New York City

-- 013 get phone number of accomplice by checking who Taylor had a phone call wiht using the numbers

SELECT receiver
   ...> FROM phone_calls
   ...> WHERE month = 7 AND day = 28 AND year = 2021
   ...> AND duration <= 60
   ...> AND caller = '(367) 555-5533';
+----------------+
|    receiver    |
+----------------+
| (375) 555-8161 |

-- 014 Get name of receiver using people table

SELECT name
   ...> FROM people
   ...> WHERE phone_number = '(375) 555-8161';
+-------+
| name  |
+-------+
| Robin |