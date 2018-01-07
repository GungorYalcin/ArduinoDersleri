<?php
  require("KoalaDBSabit.php");
 
  $connectionInfo = array( "Database"=>DB_NAME, "UID"=>DB_USER, "PWD"=>DB_PASS);
  $baglanti = sqlsrv_connect( DB_SERVER, $connectionInfo);
  
?>
