using System;
using System.Globalization;
using MySqlConnector;

namespace Calc
{
  class Program
  {
    static void Main(string[] Args)
    {
      MySqlConnection conn;
      MySqlCommand cmd;
      MySqlConnectionStringBuilder builder = new MySqlConnectionStringBuilder
      {
        Server = "localhost",
        Database = "gaussian",
        UserID = "root",
        Password = "root123",
        SslMode = MySqlSslMode.Required,
      };
      int i;
      double x, prob;
      CultureInfo.DefaultThreadCurrentCulture = new CultureInfo("en-US");
      try
      {
        
        conn = new MySqlConnection(builder.ConnectionString);
        conn.Open();
        cmd = conn.CreateCommand();
        cmd.CommandText = "DROP TABLE IF EXISTS cs_serial; CREATE TABLE cs_serial(id INTEGER AUTO_INCREMENT " +
        "PRIMARY KEY, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL)";
        cmd.ExecuteNonQuery();
        for (i = -500; i <= 500; i++)
        {
          x = (double)i / 100.0;
          prob = Gaussian.GaussianCDF(0, 1, x);
          cmd.CommandText = $"INSERT INTO cs_serial(z_score, cumulative_distribution) VALUES ({x:0.00}, {prob:0.000000});";
          cmd.ExecuteNonQuery();
        }
        conn.Close();
      }
      catch (System.Exception e)
      {
        Console.WriteLine(e.Message);
      }
    }
  }
}
