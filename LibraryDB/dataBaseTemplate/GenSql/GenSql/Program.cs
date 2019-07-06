using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace GenSql
{
    class Program
    {
        static void Main(string[] args)
        {
            using (StreamWriter outStr = new StreamWriter("sql.sql"))
            {
                //Employees
                for(int i=0;i<1000;i++)
                {
                    outStr.WriteLine("INSERT INTO Employees(firstName, lastName, patronymic, yearBirth, numberPassport, SNILS, INN, yearBeg, education, experience)"+
"VALUES('Имя"+i.ToString()+ "', 'Фамилия"+i.ToString()+"', 'Отчество"+i.ToString()+"', '1990-01-01', '000000000"+ i.ToString()+"', '000000000"+i.ToString()+"', '000000000"+i.ToString()+"', '2015-10-10', 'Высшее', '3');");
                }

                //Departments
                for (int i = 0; i < 1000; i++)
                {
                    outStr.WriteLine("INSERT INTO Departments(name,description,director)"+
"VALUES('Отдел"+i.ToString()+"', 'Описание" + i.ToString() + "', '" + i.ToString() + "'); ");
                }

                //Posts
                for (int i = 0; i < 1000; i++)
                {
                    outStr.WriteLine("INSERT INTO Posts(name, description, salary)"+
"VALUES('Пост"+i.ToString()+ "', 'Описание" + i.ToString() + "', '1000');");
                }

                //Salaries
                for (int i = 0; i < 1000; i++)
                {
                    outStr.WriteLine("INSERT INTO Salaries(employee,month,salary,year,status,post)"+
"VALUES("+i.ToString()+ ", " + (i%12).ToString() + ", 10000, 2009, 0, " + i.ToString() + "); ");
                }
            }
        }
    }
}
