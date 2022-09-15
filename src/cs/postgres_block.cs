using System;
using System.Globalization;
using Npgsql;

namespace Calc
{
  class Program
  {
    static void Main(string[] Args)
    {
      NpgsqlConnection conn;
      NpgsqlCommand cmd;
      string query = "";
      int i;
      double x, prob;
      CultureInfo.DefaultThreadCurrentCulture = new CultureInfo("en-US");
      try
      {
        conn = new NpgsqlConnection("Host=localhost;Username=root;Password=root123;Database=gaussian");
        conn.Open();
        cmd = conn.CreateCommand();
        cmd.CommandText = "DROP TABLE IF EXISTS tb_cs_block; CREATE TABLE tb_cs_block(id SERIAL " +
        "PRIMARY KEY, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL)";
        cmd.ExecuteNonQuery();
        for (i = -500; i <= 500; i++)
        {
          x = (double)i / 100.0;
          prob = Gaussian.GaussianCDF(0, 1, x);
          query += $"INSERT INTO tb_cs_block(z_score, cumulative_distribution) VALUES ({x:0.00}, {prob:0.000000});";
        }
        cmd.CommandText = query;
        cmd.ExecuteNonQuery();
        conn.Close();
      }
      catch (System.Exception e)
      {
        Console.WriteLine(e.Message);
      }
    }
  }
}
