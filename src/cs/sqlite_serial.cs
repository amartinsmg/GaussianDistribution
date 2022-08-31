// using System;
using System.Globalization;
using System.Data.SQLite;

namespace Calc
{
  class Program
  {
    static void Main(string[] Args)
    {
      string databasePath = AppDomain.CurrentDomain.BaseDirectory + "../sqlite/database.db";
      int i;
      double x, cumulativeD;
      var db = new SQLiteConnection($"URI=file:{databasePath}");
      db.Open();
      var cmd = new SQLiteCommand(db);
      CultureInfo.DefaultThreadCurrentCulture = new CultureInfo("en-US");
      cmd.CommandText = "DROP TABLE IF EXISTS cs_serial; CREATE TABLE cs_serial(id INTEGER PRIMARY KEY " +
      "AUTOINCREMENT, z_score REAL NOT NULL, cumulative_distribution REAL NOT NULL)";
      cmd.ExecuteNonQuery();
      for (i = -500; i <= 500; i++)
      {
        x = (double)i / 100.0;
        cumulativeD = Gaussian.GaussianCDF(0, 1, x);
        cmd.CommandText = $"INSERT INTO cs_serial(z_score, cumulative_distribution) VALUES ({x:0.00}, {cumulativeD:0.000000});";
        cmd.ExecuteNonQuery();
      }
      db.Close();
    }
  }
}
