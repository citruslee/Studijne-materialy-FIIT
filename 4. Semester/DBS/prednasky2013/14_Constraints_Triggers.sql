CREATE TABLE beers(
	id BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY,
	name varchar(20) NOT NULL,
	degrees DECIMAL(3,1)
);

-- vidime, ze NULL constraint funguje
INSERT INTO beers(name,degrees) VALUES ('Bernard Tmavy', 2);
INSERT INTO beers(name,degrees) VALUES (null,3);
INSERT INTO beers(name,degrees) VALUES ('Hoegaarden', null);

-- vidime,ze NULL constraint nefunguje
-- http://dev.mysql.com/doc/refman/5.5/en/insert.html
-- For multiple-row INSERT statements or INSERT INTO ... SELECT statements, 
-- the column is set to the implicit default value for the column data type. 
-- This is 0 for numeric types, the empty string ('') for string types, and 
-- the “zero” value for date and time types.

INSERT INTO beers(name,degrees) VALUES 
('Plzen',5),
-- (NULL,3),
('Hoegaarden', NULL),
('Bernard Tmavy', 2);

-- If you update a column that has been declared NOT NULL by setting to NULL, 
-- an error occurs if strict SQL mode is enabled
UPDATE beers SET name = NULL WHERE degrees IS NULL;

DROP TABLE beers;
TRUNCATE beers;
SELECT * FROM beers;

-- PrimaryKey constraint snad funguje
INSERT INTO beers(id,name,degrees) VALUES (1,'Zlaty Bazat', 2);
UPDATE beers set id = 1 where name LIKE 'Hoegaard%';

-- UNIQUE constraint
DROP TABLE beers;
CREATE TABLE beers(
	id BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY,
	name varchar(20) NOT NULL UNIQUE,
	degrees DECIMAL(2,1)
);

INSERT INTO beers(name,degrees) VALUES 
('Budvar', 5),
('Budvar', 6);

-- mozem povedat, ze UNIQUE ma byt az dvojica (meno, stupne)
DROP TABLE beers;
CREATE TABLE beers(
	id BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY,
	name varchar(20) NOT NULL,
	degrees DECIMAL(3,1),
	CONSTRAINT UNIQUE (name,degrees)
);

SELECT * FROM beers;

-- a ked sa pokusim vlozit tam dvojicu, ktoru uz raz mam...
INSERT INTO beers(name,degrees) VALUES 
('Budvar', 5);

-- ako vzdy bacha na NULL
INSERT INTO beers(name,degrees) VALUES 
('Cerna Hora', NULL);
INSERT INTO beers(name,degrees) VALUES 
('Cerna Hora', NULL);

SELECT * FROM beers;

-- teraz musime ist do PostgreSQL
DROP TABLE beers;
CREATE TABLE beers(
	id BIGINT NOT NULL PRIMARY KEY,
	name varchar(20) NOT NULL,
	degrees DECIMAL(3,1) CONSTRAINT stupne CHECK (degrees > 0 AND degrees < 25)
);
INSERT INTO beers(id,name,degrees) VALUES (123,'Zlaty Bazant', -2);
INSERT INTO beers(id,name,degrees) VALUES (456,'Vodka Extra Jemna', 40);

-- teraz musime ist do PostgreSQL
DROP TABLE beers;
CREATE TABLE beers(
	id BIGINT NOT NULL PRIMARY KEY,
	name varchar(20) NOT NULL,
	degrees DECIMAL(3,1),
	CONSTRAINT stupne CHECK (degrees > 0 OR name = 'Zlaty Bazant')
);

-- TRIGGERs
delimiter |
CREATE TRIGGER uspesni_studenti_jedia_v_hornej
AFTER INSERT ON students
FOR EACH ROW BEGIN
	IF NEW.vsp < 2 THEN
		INSERT INTO lunches(student_id,restaurant_id) VALUES (NEW.id,1);
	END IF;
  END;
|
delimiter ;

select * from students s
join lunches l ON s.id = l.student_id;

INSERT INTO students(name,vsp) VALUES ('Misko Sikovny',1.2);
INSERT INTO students(name,vsp) VALUES ('Misko Sikovny',2.1);

-- CHECK constraint v MySQL...

DROP PROCEDURE IF EXISTS raise_application_error;
DROP PROCEDURE IF EXISTS get_last_custom_error;
DROP TABLE IF EXISTS RAISE_ERROR;

DELIMITER $$
CREATE PROCEDURE raise_application_error(IN CODE INTEGER, IN MESSAGE VARCHAR(255)) SQL SECURITY INVOKER DETERMINISTIC
BEGIN
  CREATE TEMPORARY TABLE IF NOT EXISTS RAISE_ERROR(F1 INT NOT NULL);

  SELECT CODE, MESSAGE INTO @error_code, @error_message;
  INSERT INTO RAISE_ERROR VALUES(NULL);
END;
$$

CREATE PROCEDURE get_last_custom_error() SQL SECURITY INVOKER DETERMINISTIC
BEGIN
  SELECT @error_code, @error_message;
END;
$$
DELIMITER ; 

CALL raise_application_error(1234, 'Custom message');
CALL get_last_custom_error();

DROP TABLE beers;
CREATE TABLE beers(
	id BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY,
	name varchar(20) NOT NULL,
	degrees DECIMAL(3,1)
);

DROP TRIGGER pivo_nema_nulu;

delimiter |
CREATE TRIGGER pivo_nema_nulu
BEFORE INSERT ON beers
FOR EACH ROW BEGIN
	IF NEW.degrees <= 1 AND NEW.name <> 'Zlaty Bazant' THEN
		CALL raise_application_error(777,'pivo nema nulu!');
	END IF;
  END;
|
delimiter ;


INSERT INTO beers(name,degrees) VALUES('Stein',3);
INSERT INTO beers(name,degrees) VALUES('Stein',-3);
INSERT INTO beers(name,degrees) VALUES('Zlaty Bazant',-3);

SELECT * from beers;

SELECT * FROM students s
JOIN lunches l ON l.student_id = s.id;

DELETE FROM lunches where student_id = 17;
DELETE FROM students where id = 17;
