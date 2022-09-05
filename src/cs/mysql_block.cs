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
      string query = "";
      int i;
      double x, prob;
      CultureInfo.DefaultThreadCurrentCulture = new CultureInfo("en-US");
      conn = new MySqlConnection(builder.ConnectionString);
      conn.Open();
      cmd = conn.CreateCommand();
      cmd.CommandText = "DROP TABLE IF EXISTS cs_block; CREATE TABLE cs_block(id INTEGER AUTO_INCREMENT " +
      "PRIMARY KEY, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL)";
      cmd.ExecuteNonQuery();
      for (i = -500; i <= 500; i++)
      {
        x = (double)i / 100.0;
        prob = Gaussian.GaussianCDF(0, 1, x);
        query += $"INSERT INTO cs_block(z_score, cumulative_distribution) VALUES ({x:0.00}, {prob:0.000000});";
      }
      cmd.CommandText = query;
      cmd.ExecuteNonQuery();
      conn.Close();
    }
  }
}