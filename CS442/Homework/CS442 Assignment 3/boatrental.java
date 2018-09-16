/**
 * Kaitlynn Prescott (kprescot)
 * I pledge my honor that I have abided by the stevens honor system.
 * 
 */

import java.sql.*;

public class boatrental {
    // JDBC driver name and database URL
    static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
    static final String DB_URL = "jdbc:mysql://localhost/test?useSSL=false";

    //  Database credentials
    static final String USER = "root";
    //the user name; You can change it to your username (by default it is root).
    static final String PASS = "root";
    //the password; You can change it to your password (the one you used in MySQL server configuration).

    public static void main(String[] args) {
        Connection conn = null;
        Statement stmt = null;
        try{
            //STEP 1: Register JDBC driver
            Class.forName("com.mysql.jdbc.Driver");

            //STEP 2: Open a connection to database
            System.out.println("Connecting to database...");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            System.out.println("Creating database...");
            stmt = conn.createStatement();

            //STEP 3: Use SQL to Create Database;
            String sql = "CREATE DATABASE BoatRental";
            stmt.executeUpdate(sql);
            System.out.println("Database created successfully...");

            //STEP 4: Use SQL to select the database;
            sql = "use BoatRental";
            stmt.executeUpdate(sql);

            //STEP 5: Use SQL to create Tables;
            //Create Table Sailor;
            //Sailor(sid  integer, sname varchar(20), rating real, age integer)

            sql = "create table sailor( sid integer not null PRIMARY KEY, " +
                    "sname varchar(20) not null," +
                    "rating real," +
                    "age integer not null)";
            stmt.executeUpdate(sql);

            //Create Table Boats;
            //Boats (bid integer, bname varchar(40), color varchar(40))
            
            sql = "create table boats(bid integer not null PRIMARY KEY," +
                    "bname varchar(40) not null," +
                    "color varchar(40))";
            stmt.executeUpdate(sql);

            //Create Table Reserves;
            //Reserves(sid integer, bid integer, day date)
            
            sql = "create table reserves(sid integer not null REFERENCES sailor(sid)," +
                    "bid integer not null REFERENCES boats(bid)," +
                    "day date not null,"+
                    "PRIMARY KEY (sid, bid, day))";
            stmt.executeUpdate(sql);



            //STEP 6: Use SQL to insert tuples into tables;
            //Insert tuples into Table Sailor;

            sql = "insert into sailor values(22, 'Dustin', 7, 45)";
            stmt.executeUpdate(sql);

            sql = "insert into sailor values(29, 'Brutus', 1, 33)";
            stmt.executeUpdate(sql);

            sql = "insert into sailor values(31, 'Lubber', 8, 55)";
            stmt.executeUpdate(sql);

            sql = "insert into sailor values(32, 'Andy', 8, 26)";
            stmt.executeUpdate(sql);

            sql = "insert into sailor values(58, 'Rusty', 10, 35)";
            stmt.executeUpdate(sql);

            sql = "insert into sailor values(64, 'Horatio', 7, 35)";
            stmt.executeUpdate(sql);

            sql = "insert into sailor values(71, 'Zorba', 20, 18)";
            stmt.executeUpdate(sql);

            sql = "insert into sailor values(74, 'Horatio', 9, 35)";
            stmt.executeUpdate(sql);


            //Insert tuples into Table Boats;
            
            sql = "insert into boats values(101, 'Interlake', 'blue')";
            stmt.executeUpdate(sql);

            sql = "insert into boats values(102, 'Interlake', 'red')";
            stmt.executeUpdate(sql);

            sql = "insert into boats values(103, 'Clipper', 'green')";
            stmt.executeUpdate(sql);

            sql = "insert into boats values(104, 'Marine', 'red')";
            stmt.executeUpdate(sql);


            //Insert tuples into Table Reserves;
            
            sql = "insert into reserves values(22, 101, '2008-10-10')";
            stmt.executeUpdate(sql);

            sql = "insert into reserves values(22, 102, '2008-10-10')";
            stmt.executeUpdate(sql);

            sql = "insert into reserves values(22, 103, '2009-10-08')";
            stmt.executeUpdate(sql);

            sql = "insert into reserves values(22, 104, '2009-10-09')";
            stmt.executeUpdate(sql);

            sql = "insert into reserves values(31, 102, '2008-11-10')";
            stmt.executeUpdate(sql);

            sql = "insert into reserves values(31, 103, '2008-11-06')";
            stmt.executeUpdate(sql);

            sql = "insert into reserves values(31, 104, '2008-11-12')";
            stmt.executeUpdate(sql);

            sql = "insert into reserves values(64, 101, '2008-09-05')";
            stmt.executeUpdate(sql);

            sql = "insert into reserves values(64, 102, '2008-09-08')";
            stmt.executeUpdate(sql);

            sql = "insert into reserves values(74, 103, '2008-09-08')";
            stmt.executeUpdate(sql);



            //STEP 7: Use SQL to ask queries and retrieve data from the tables;

            //Q1: Find the sids of all sailors who have reserved red boats but not green boats
            System.out.println ("--- Query 1 ---");
            Statement s1 = conn.createStatement ();
            s1.executeQuery ("SELECT R.sid FROM boats B, reserves R WHERE R.bid = B.bid AND B.color = 'red' AND R.sid NOT IN (SELECT R1.sid FROM boats B1, reserves R1 WHERE B1.bid = R1.bid AND B1.color = 'green')");
            ResultSet rs1 = s1.getResultSet ();
            int count1 = 0;
            while (rs1.next ())
            {
                int idVal = rs1.getInt ("sid");
                System.out.println (
                        "sid = " + idVal);
                ++count1;
            }
            rs1.close ();
            s1.close ();
            System.out.println (count1 + " rows were retrieved");
            System.out.println("---------------");

            //Q2: Find the names of sailors who have NOT reserved a red boat
            System.out.println ("--- Query 2 ---");
            Statement s2 = conn.createStatement ();
            s2.executeQuery ("SELECT S.sname FROM sailor S WHERE S.sid NOT IN (SELECT R.sid FROM boats B, reserves R WHERE R.sid = S.sid AND R.bid = B.bid AND B.color = 'red')");
            ResultSet rs2 = s2.getResultSet ();
            int count2 = 0;
            while (rs2.next ())
            {
                String nameVal = rs2.getString ("sname");
                System.out.println ("sailor name = " + nameVal);
                ++count2;
            }
            rs2.close ();
            s2.close ();
            System.out.println (count2 + " rows were retrieved");
            System.out.println("---------------");

            //Q3: Find sailors whose rating is better than every sailor named Horatio.
            System.out.println ("--- Query 3 ---");
            Statement s3 = conn.createStatement ();
            s3.executeQuery ("SELECT * FROM sailor S WHERE S.rating > ALL (SELECT S1.rating FROM sailor S1 WHERE S1.sname = 'Horatio')");
            ResultSet rs3 = s3.getResultSet ();
            int count3 = 0;
            while (rs3.next ())
            {
                String nameVal = rs3.getString ("sname");
                System.out.println ("sailor name = " + nameVal);
                ++count3;
            }
            rs3.close ();
            s3.close ();
            System.out.println (count3 + " rows were retrieved");
            System.out.println("---------------");

            //Q4: Find the names of sailors who have reserved all boats.
            System.out.println ("--- Query 4 ---");
            Statement s4 = conn.createStatement ();
            s4.executeQuery ("SELECT S.sname FROM sailor S WHERE NOT EXISTS (SELECT B.bid FROM boats B WHERE NOT EXISTS (SELECT R.bid FROM reserves R WHERE R.bid = B.bid AND R.sid = S.sid))");
            ResultSet rs4 = s4.getResultSet ();
            int count4 = 0;
            while (rs4.next ())
            {
                String nameVal = rs4.getString ("sname");
                System.out.println ("sailor name = " + nameVal);
                ++count4;
            }
            rs4.close ();
            s4.close ();
            System.out.println (count4 + " rows were retrieved");
            System.out.println("---------------");

            //Q5: For each red boat, find its number of reservations.
            System.out.println ("--- Query 5 ---");
            Statement s5 = conn.createStatement ();
            s5.executeQuery ("SELECT B.bid, COUNT(*) AS numres FROM boats B, reserves R WHERE R.bid = B.bid AND B.color = 'red' GROUP BY B.bid");
            ResultSet rs5 = s5.getResultSet ();
            int count5 = 0;
            while (rs5.next ())
            {
                int idVal = rs5.getInt ("bid");
                int numresVal = rs5.getInt ("numres");
                System.out.println (
                        "Boat id = " + idVal +
                                " Number of Reservations = " + numresVal);
                ++count5;
            }
            rs5.close ();
            s5.close ();
            System.out.println (count5 + " rows were retrieved");
            System.out.println("---------------");



            sql = "DROP DATABASE BoatRental";
            stmt.executeUpdate(sql);
            System.out.println("Database dropped successfully...");




        }catch(SQLException se){
            //Handle errors for JDBC
            se.printStackTrace();
        }catch(Exception e){
            //Handle errors for Class.forName
            e.printStackTrace();
        }finally{
            //finally block used to close resources
            try{
                if(stmt!=null)
                    stmt.close();
            }catch(SQLException se2){
            }// nothing we can do
            try{
                if(conn!=null)
                    conn.close();
            }catch(SQLException se){
                se.printStackTrace();
            }//end finally try
        }//end try
        System.out.println("Goodbye!");
    }//end main
}
