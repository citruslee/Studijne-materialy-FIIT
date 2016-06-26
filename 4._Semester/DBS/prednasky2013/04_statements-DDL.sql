CREATE  TABLE `dbs_example`.`restaurants` (
  `id` BIGINT NOT NULL AUTO_INCREMENT ,
  `name` VARCHAR(45) NOT NULL ,
  `capacity` INT NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_unicode_ci;

CREATE  TABLE `dbs_example`.`students` (
  `id` BIGINT NOT NULL AUTO_INCREMENT ,
  `name` VARCHAR(45) NOT NULL ,
  `vsp` FLOAT NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_unicode_ci;


CREATE  TABLE `dbs_example`.`lunches` (
  `id` BIGINT NOT NULL AUTO_INCREMENT ,
  `student_id` BIGINT NOT NULL ,
  `restaurant_id` BIGINT NOT NULL ,
  `was_tasty` BOOLEAN NULL ,
  PRIMARY KEY (`id`),
  INDEX fk_student(`student_id` ASC) ,
  INDEX fk_restaurants(`restaurant_id` ASC),
  CONSTRAINT `fk_student`
  FOREIGN KEY (`student_id`) REFERENCES `students` (`id`)
    ON UPDATE CASCADE
    ON DELETE RESTRICT,
  CONSTRAINT `fk_restaurant`
  FOREIGN KEY (restaurant_id) REFERENCES restaurants(id)
    ON UPDATE CASCADE
    ON DELETE RESTRICT
  )
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_unicode_ci;

INSERT INTO `dbs_example`.`lunches` (`student_id`, `restaurant_id`, `was_tasty?`) VALUES (2, 3, true);

INSERT INTO students(id,name,vsp) VALUES
  (1,'Jozko Mrkvicka', 3.9),
  (2,'Ferko Fazulka', 2.1),
  (3,'Zuzka Hraskova', 1.2),
  (4,'Katka Malinova', 2.5),
  (5,'Petko Egresovy', 1.2),
  (6,'Janko Zemiakovy', 1.7),
  (7,'Zuzka Hraskova', 2.2);

INSERT INTO restaurants(id,name,capacity) VALUES
  (1,'horna', 300),
  (2,'dolna', 150),
  (3,'studentska', 80),
  (4,'prifuk', 60),
  (5,'palmyra', 50);
  
INSERT INTO lunches(student_id,restaurant_id,was_tasty) VALUES
  (1,2,true),
  (1,3,false),
  (2,1,true),
  (2,5,true),
  (3,1,false),
  (3,4,true),
  (4,3,false),
  (4,4,false),
  (5,1,true),
  (5,1,true);
