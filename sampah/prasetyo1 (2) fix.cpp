#include <ESP8266WiFi.h>                         //Memasukkan library WiFi ESP8266
#include <DallasTemperature.h>                   //Memasukkan library sensor suhu Dallas
#include <OneWire.h>                             //Memasukkan library OneWire

const char* ssid = "PRASETYO";                      //Nama SSID AP
const char* password = "suhuds18b20";                 //Password WiFi

const int sensorsuhu = D0;                       //Inisialisasi sensorsuhu pada pin GPIO4 atau D2 

OneWire oneWire (sensorsuhu);                    //Komunikasi OneWire ke sensorsuhu
DallasTemperature sensors(&oneWire);             //Komunikasi sensorsuhu dari OneWire

WiFiServer server (80);                          //Menyatakan WebServer pada port 80   

void setup(void){                                //Inisialisasi awal sebelum program mulai berjalan
 Serial.begin(115200);                           //Serial monitor menggunakan baudrate 115200
 delay (10);                                     //Jeda waktu 0,01 detik
 pinMode(sensorsuhu, OUTPUT);                    //Mengatur sensorsuhu sebagai OUTPUT
 digitalWrite(sensorsuhu, LOW);                  //Kondisi awal sensorsuhu OFF
  
 Serial.println();                               //Menambahkan baris baru pada Serial Monitor
 Serial.print ("Menghubungkan ke ");             //Menampilkan teks Menghubungkan ke jaringan WiFi
 Serial.println(ssid);                           //Menampilkan nilai dari ssid/nama jaringan WiFi ke dalam Serial Monitor.
 WiFi.begin(ssid,password);                      //Memulai koneksi WiFi dengan mencocokan ssid dan password
 
 while (WiFi.status() !=WL_CONNECTED) {          //Proses pembacaan status WiFi
 delay(50);                                     //Jeda waktu 0,05 detik
 Serial.print("."); }                           //Menuliskan . terus menerus selama proses pembacaan WiFi pada Serial Monitor
 Serial.println("");                             //Menampilkan baris kosong pada Serial Monitor
 Serial.print("WiFi terhubung");                 //Menampilkan teks "WiFi terhubung" pada Serial Monitor

 Serial.println("IP address:");                  //Menampilkan teks "IP address:" pada Serial Monitor
 Serial.println(WiFi.localIP());                 //Menampilkan alamat IP lokal pada Serial Monitor
 server.begin();                                 //Memulai server pada board
 Serial.println("NodeMCU server terhubung");     //Menampilkan teks "NodeMCU server terhubung" pada Serial Monitor
}                                                //Menutup perintah blok program didalam {}

void loop(void)                                            //Menjalankan program secara berulang-ulang
{                                                          //Membuka perintah blok program didalam {}
 sensors.requestTemperatures();                            //Meminta pembacaan suhu dari sensor suhu yang terhubung ke board
 float suhuCelcius = sensors.getTempCByIndex(0);           //Mengambil nilai suhu dalam satuan Celcius dari sensorsuhu yang terhubung ke board
 float suhuFahrenheit = sensors.getTempFByIndex(0);        //Mengambil nilai suhu dalam satuan Fahrenheit dari sensorsuhu yang terhubung ke board
 float suhuReaumur = suhuCelcius * 0.8;                    //Mengambil nilai suhu dalam satuan Réaumur dari suhuCelcius * 0.8
 float suhuKelvin = suhuCelcius + 273.15;                  //Mengambil nilai suhu dalam satuan Kelvin dari suhuCelcius + 273.15
  
 Serial.print("Suhu Celcius:");                  //Menampilkan teks "Suhu Celcius:" pada Serial Monitor
 Serial.println(suhuCelcius);                    //Menampilkan nilai suhu Celcius pada Serial Monitor
 Serial.println();                               //Menambahkan baris baru pada Serial Monitor
 Serial.print("Suhu Fahrenheit:");               //Menampilkan teks "Suhu Fahrenheit:" pada Serial Monitor
 Serial.println(suhuFahrenheit);                 //Menampilkan nilai suhu Fahrenheit pada Serial Monitor
 Serial.println();                               //Menambahkan baris baru pada Serial Monitor
 Serial.print("Suhu Reaumur:");                  //Menampilkan teks "Suhu Reaumur:" pada Serial Monitor
 Serial.println(suhuReaumur);                    //Menampilkan nilai suhu Reaumur pada Serial Monitor
 Serial.println();                               //Menambahkan baris baru pada Serial Monitor
 Serial.print("Suhu Kelvin:");                   //Menampilkan teks "Suhu Kelvin:" pada Serial Monitor
 Serial.println(suhuKelvin);                     //Menampilkan nilai suhu Kelvin pada Serial Monitor
 Serial.println();                               //Menambahkan baris baru pada Serial Monitor

WiFiClient client = server.available();          //Menerima koneksi dari klien web
if (client)                                      //Jika klien web terhubung,maka baris kode berikutny akana dijalankan
 {                                               //Membuka perintah blok program didalam {}
 Serial.println("Web Client terhubung");         //Menampilkan teks "Web Client terhubung" pada Serial Monitor
 String request = client.readStringUntil('\r');  //Membaca permintaan klien web hingga karakter '\r' ditemukan
 client.println("HTTP/1.1 200 OK");              //Mengirimkan respon HTTP dengan kode status 200 (OK) ke klien web
 client.println("Content-type:text/html");       //Mengirimkan tipe konten respons (content-type) ke klien web
 client.println("Connection:close");             //Menutup koneksi dengan klien web setelah selesai mengirimkan respons
  client.println("Client Tidak Terhubung");      //Menampilkan teks "Client Tidak Terhubung" pada Serial Monitor
 client.println();                               //Mengirimkan baris kosong ke klien web

 client.println("<!DOCTYPE html>");                                                                     //Mendefinisikan tipe dokumen HTML yang digunakan
 client.println("<html>");                                                                              //Membuka tag html
 client.println("<center>");                                                                            //Mengatur tampilan HTML di tengah halaman
 client.println("<head><meta http-equiv=\"refresh\"content=\"360\"></head>");                           //Memberikan atribut refresh setiap 2 detik untuk memperbarui halaman otomatis
 client.println("<body style=\"background-image:url('https://i.postimg.cc/bvrDqb94/F79297-C2-C860-4873-9238-2514-B871-C298.jpg');background-repeat:no-repeat; background-attachment: fixed; background-size: cover;\">");  
 client.println("<img src=\"https://i.postimg.cc/kXWWHxTc/FAC1-EAED-5-DB3-4-C1-C-A2-C0-2845-A24-F91-DF.jpg\" width=\"200\" height=\"300\">");
 client.println("<h1 style=\"font-family:monaco; color: red; font-size:35px\">WEB SERVER SENSOR SUHU DALLAS  </h1>");                                                    //Menampilkan heading level 1 dan memberikan judul "WEB SERVER SENSOR SUHU DALLAS" pada WebServer
 client.println("<h2 style=\"font-family:monaco; color: blue;font-size:20px\">AGUS PRASETYO </h2>");                                                                    //Menampilkan heading level 2 dan memberikan judul "AGUS PRASETYO" pada WebServer
 client.println("<h3 style=\"font-family:monaco; color: black;font-size:20px\">02421013</h3>");                                                                        //Menampilkan heading level 3 dan memberikan judul "02421013" pada WebServer
 client.println("<h4 style=\"font-family:monaco; color: green;font-size:20px\">KELAS A</h4> ");                                                                       //Menampilkan heading level 4 dan memberikan judul "KELAS A" pada WebServer
                                                              
 client.println("<p><span style=\"border:5px solid white;background-color:LawnGreen\">Suhu Dalam Celcius = \"");             //Menampilkan paragraph dengan atribut warna, ketebalan garis, dan teks "Suhu Dalam Celcius ="  
 client.println(suhuCelcius);                                                                                                //Menampilkan nilai suhu Celcius pada WebServer
 client.println(" °Celcius</span><p>");                                                                                      //Menampilkan paragraph menuliskan " °Celcius" yaitu satuan Celcius
 client.println("<p><span style=\"border:5px solid white;background-color:Red\">Suhu Dalam Fahrenheit =\"");                 //Menampilkan paragraph dengan atribut warna, ketebalan garis, dan teks "Suhu Dalam Fahrenheit ="
 client.println(suhuFahrenheit);                                                                                             //Menampilkan nilai suhu Fahrenheit pada WebServer
 client.println(" °Fahrenheit</span><p>");                                                                                   //Menampilkan paragraph menuliskan " °Fahrenheit" yaitu satuan Fahrenheit
 client.println("<p><span style=\"border:5px solid white;background-color:Indigo\">Suhu Dalam Reaumur =\"");                 //Menampilkan paragraph dengan atribut warna, ketebalan garis, dan teks "Suhu Dalam Reaumur ="
 client.println(suhuReaumur);                                                                                                //Menampilkan nilai suhu Reaumur pada WebServer
 client.println(" °Reaumur</span><p>");                                                                                      //Menampilkan paragraph menuliskan " °Reaumur" yaitu satuan Reaumur
 client.println("<p><span style=\"border:5px solid white;background-color:Blue\">Suhu Dalam Kelvin =\"");                    //Menampilkan paragraph dengan atribut warna, ketebalan garis, dan teks "Suhu Dalam Kelvin ="
 client.println(suhuKelvin);                                                                                                 //Menampilkan nilai suhu Kelvin pada WebServer
 client.println(" °Kelvin</span><p>");                                                                                       //Menampilkan paragraph menuliskan " °Kelvin" yaitu satuan Réaumur
 client.println("</body></html>");                                                                                           //Menutup tag body dan html
 client.println("<footer> <p>PERCOBAAN SUKSES<br></p> </footer>");
 client.println();                                                                                      //Mengirimkan baris kosong ke klien web 
 client.println("");                                                                                    //Mengirimkan pesan kosong (empty message) pada Serial Monitor
 }                                                                                                      //Menutup perintah blok program didalam {}
}                                                                                                       //Menutup perintah blok program didalam {}