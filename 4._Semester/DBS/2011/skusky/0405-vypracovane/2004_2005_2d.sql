select dbo.Predmet.rocnik, dbo.Predmet.nazov, dbo.Student.priezvisko , dbo.Student.meno
from dbo.Predmet, dbo.Student, dbo.Vyber
where dbo.Vyber.id_student = dbo.Student.id_student and dbo.Vyber.id_predmet = dbo.Predmet.id_predmet
order by dbo.Predmet.rocnik, dbo.Predmet.nazov, dbo.Student.priezvisko , dbo.Student.meno