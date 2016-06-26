select distinct dbo.StudOdbor.nazov, dbo.Student.priezvisko , dbo.Student.meno
from dbo.StudOdbor, dbo.Student, dbo.Vyber, dbo.Predmet
where dbo.Predmet.id_odbor = dbo.StudOdbor.id_odbor 
	and dbo.Vyber.id_predmet = dbo.Predmet.id_predmet
	and dbo.Vyber.id_student = dbo.Student.id_student
order by dbo.StudOdbor.nazov, dbo.Student.priezvisko , dbo.Student.meno
