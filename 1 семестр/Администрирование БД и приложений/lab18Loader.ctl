LOAD DATA
	INFILE lab18InputData.txt
	INTO TABLE SYSTEM.LoadTable
	REPLACE
	FIELDS TERMINATED BY ','
	(
		str "upper(:str)",
		num "round(:num, 2)",
		datet date "mmddyyyy"
	)