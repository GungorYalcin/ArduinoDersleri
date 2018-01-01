<?php
  require_once("baglanti.php");
  global $baglanti;

 $ip = trim($_SERVER["REMOTE_ADDR"]);
 $Tarih = date("Y-m-d h:i:s");  

   if (isset($_GET['ID']))
  {
    $KartID =$_GET['ID'];
  }

  if (isset($_POST['ID']))
  {
    $KartID =$_POST['ID'];
  }	
  
  if (isset($_POST['value']))
  {
    $deger =$_POST['value'];
  }	

  if (isset($_GET['value']))
  {
    $deger =$_GET['value'];
  }

 
     $query = "select ID from DP_Kart where ID='{$KartID}' ";
     $subject_set = sqlsrv_query( $baglanti,$query);
     $subject2 = sqlsrv_fetch_array($subject_set,SQLSRV_FETCH_ASSOC);
      if ($subject2['ID']==$KartID )
      { 
         $query = "Update DP_Kart set DEGER= {$deger}, chg_date='{$Tarih}' where ID ='{$KartID}' ";
      }
      else 
      {
         $query = "insert into DP_Kart (ID,IP,TIPI,SIRA,DEGER,chg_date) values ('{$KartID}','{$ip}',3,0,{$deger},'{$Tarih}')";
	  }
	 $stmt = sqlsrv_prepare($baglanti,$query,array());
        if( sqlsrv_execute( $stmt ) === false ) 
            echo "hata:",sqlsrv_errors();
		
	  $query = "insert into DP_Log (ID,IP,TIPI,SIRA,DEGER,chg_date) values ('{$KartID}','{$ip}',3,0,{$deger},'{$Tarih}')";
$stmt = sqlsrv_prepare($baglanti,$query,array());
        if( sqlsrv_execute( $stmt ) === false ) 
            echo "hata:",sqlsrv_errors();

sqlsrv_close($baglanti);
/*
if (file_exists("./users/sensor.txt"))
{
 $islem=fopen("./users/sensor.txt","a");
  $metin = " Tarih=".date("d/m/y H:i")." IP=".rtrim($_SERVER["REMOTE_ADDR"])." ID:".$KartID." Value:".$deger." XXX\n";
  fputs($islem,$metin);
  fclose($islem);
}
*/
echo "OK",$KartID,$deger;
?>