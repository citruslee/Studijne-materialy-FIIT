LOAD DATA LOCAL INFILE '/media/barla/old-root/home/barla/otvorenezmluvy.csv'
    INTO TABLE documents
    FIELDS TERMINATED BY ','
    OPTIONALLY ENCLOSED BY '"'
    ESCAPED BY '\"'
    LINES TERMINATED BY '\n'
    IGNORE 1 LINES
