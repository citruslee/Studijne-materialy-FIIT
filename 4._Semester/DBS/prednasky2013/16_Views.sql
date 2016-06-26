CREATE VIEW dobre_restauracie AS
SELECT distinct(restaurant_id) FROM lunches
WHERE was_tasty = true;

SELECT * FROM dobre_restauracie;

SELECT * FROM restaurants r
JOIN dobre_restauracie d ON d.restaurant_id = r.id
WHERE capacity < 100;

CREATE VIEW dobre_male_restauracie AS
SELECT * FROM restaurants r
JOIN dobre_restauracie d ON d.restaurant_id = r.id
WHERE capacity < 100;

SELECT * FROM dobre_male_restauracie;

-- POZOR, MySQL Vam toto umozni
DROP VIEW dobre_restauracie;

-- toto nam zlyha
CREATE VIEW vsetko AS
SELECT * FROM lunches l
JOIN students s ON l.student_id = s.id
JOIN restaurants r ON l.restaurant_id = r.id;

CREATE VIEW vsetko AS
SELECT 	s.id AS student_id, 
			s.name AS student_name, 
			s.vsp, 
			l.id AS lunch_id, 
			l.was_tasty, 
			r.id AS restaurant_id, 
			r.name AS restaurant_name, 
			r.capacity, 
			r.location 
FROM lunches l
JOIN students s ON l.student_id = s.id
JOIN restaurants r ON l.restaurant_id = r.id;

SELECT * FROM vsetko;

SELECT * FROM vsetko WHERE vsp < 2;

-- pokus o insert
INSERT INTO vsetko(student_id,student_name,vsp,lunch_id,was_tasty,restaurant_id,restaurant_name,capacity,location) VALUES
(50, 'Testovaci', 2.5, 64, 0, 8, 'neexistujuca', 200, fakulty);

-- pokus o delete
DELETE FROM dobre_restauracie WHERE restaurant_id = 5;

CREATE VIEW male_restauracie AS
SELECT id,name FROM restaurants
WHERE capacity < 100;

SELECT * FROM male_restauracie;

-- tento INSERT prejde, ale vo VIEW sa neprejavi
INSERT INTO male_restauracie(name) VALUES('dalsia');
SELECT * FROM restaurants;
-- DELETE nam neprejde
DELETE FROM male_restauracie WHERE id = 7;

DROP VIEW male_restauracie;
CREATE VIEW male_restauracie AS
SELECT id,name,capacity FROM restaurants
WHERE capacity < 100;

INSERT INTO male_restauracie(name, capacity) VALUES('dalsia3', 500);
DELETE FROM male_restauracie WHERE id = 9;

CREATE VIEW male_restauracie2 AS
SELECT id,name,capacity FROM restaurants
WHERE capacity < 100
WITH CHECK OPTION;

INSERT INTO male_restauracie2(name) VALUES('este dalsia');

CREATE VIEW nespokojni_studenti AS
SELECT * FROM students s
WHERE s.id IN (SELECT student_id FROM lunches WHERE was_tasty = false);

SELECT * FROM nespokojni_studenti;

SELECT * FROM students;

DELETE FROM nespokojni_studenti WHERE id = 4;

CREATE VIEW obedy_v_hornej(s_id, l_id, name, was_tasty) AS
SELECT s.id, l.id, s.name, l.was_tasty 
FROM students s
JOIN lunches l ON s.id = l.student_id
WHERE l.restaurant_id = 1;


SELECT * FROM obedy_v_hornej;

UPDATE obedy_v_hornej 
SET name = CONCAT_WS(' ', name, "nespokojna") 
WHERE was_tasty = false;

