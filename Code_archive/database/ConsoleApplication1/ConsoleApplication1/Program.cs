using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Configuration;
using System.Data.SqlClient;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {
            var connectionString = ConfigurationManager.ConnectionStrings["default"].ConnectionString;

            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                SqlCommand command = connection.CreateCommand();
                command.CommandText = "SELECT id_publishing_house, name, id_city FROM dbo.Publishing_houses";

                connection.Open();
                SqlDataReader reader = command.ExecuteReader();

                while (reader.Read())
                {
                    //int id = reader.GetInt32(0);
                    int id = (int)reader["id_publishing_house"];
                    string name;

                    if (reader.IsDBNull(1) || reader["name"] is DBNull)
                        name = null;
                    else
                        name = (string)reader["name"];

                    int? city = reader["id_city"] as int?;

                    Console.WriteLine(id + " " + name + " " + city);
                }
            }
        }
    }
}

//EPA.ms/xt2016-2