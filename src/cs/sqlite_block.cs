using System;
using System.Globalization;
using System.Data.SQLite;

namespace Calc
{
  class Program
  {
    static void Main(string[] Args)
    {
      SQLiteConnection conn;
      SQLiteCommand cmd;
      string query = "",
        databasePath = AppDomain.CurrentDomain.BaseDirectory + "../sqlite/database.db";
      int i;
      double x, cumulativeD;
      CultureInfo.DefaultThreadCurrentCulture = new CultureInfo("en-US");
      conn = new SQLiteConnection($"URI=file:{databasePath}");
      conn.Open();
      cmd = new SQLiteCommand(conn);
      cmd.CommandText = "DROP TABLE IF EXISTS cs_block; CREATE TABLE cs_block(id INTEGER PRIMARY KEY " +
      "AUTOINCREMENT, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL)";
      cmd.ExecuteNonQuery();
      for (i = -500; i <= 500; i++)
      {
        x = (double)i / 100.0;
        cumulativeD = Gaussian.GaussianCDF(0, 1, x);
        query += $"INSERT INTO cs_block(z_score, cumulative_distribution) VALUES ({x:0.00}, {cumulativeD:0.000000});";
      }
      cmd.CommandText = query;
      cmd.ExecuteNonQuery();
      conn.Close();
    }
  }
}
