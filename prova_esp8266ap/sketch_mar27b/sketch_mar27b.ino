//A simplified version of work begun by Tzapu and chriscook8
    //for saving local WiFi SSID and Passwords to the ESP8266.
    //Uses ESP8266 internal memory instead of the problematic EEPROM.
    //To input local SSID and Password, connect to WiFi "ESP8266",
    //and point your browser to "192.168.4.1".
    
    #include "ESP8266WiFi.h"
    #include <ESP8266mDNS.h>
    #include <WiFiClient.h>
    #include <BlynkSimpleEsp8266.h>
    
    MDNSResponder mdns;
    WiFiServer server(80);
    
    char auth[] = "3b8dfe66343d4a02a41809810fac010d"; // Blynk token
    const char* APssid = "tenda"; // Name of access point
    
    String st;
    String rsid;
    String rpass;
    boolean newSSID = false;
    
    
    void setup() {
      Serial.begin(115200);
      delay(10);
      Serial.println("Startup");
    
      // if the stored SSID and password connected successfully, exit setup
      if ( testWifi()) {
              Blynk.config(auth);
              return;
          }
      // otherwise, set up an access point to input SSID and password     
      else
          Serial.println("");
          Serial.println("Connect timed out, opening AP"); 
          setupAP();
    }
    
    int testWifi(void) {
      int c = 0;
      Serial.println("Waiting for Wifi to connect");  
      while ( c < 20 ) {
        if (WiFi.status() == WL_CONNECTED) {
          Serial.println("WiFi connected.");
          return(1); 
          }      
        delay(500);
        Serial.print(WiFi.status());    
        c++;
      }
      return(0);
    } 
    
    void launchWeb(int webtype) {
        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println(WiFi.localIP());
        Serial.println(WiFi.softAPIP());
        if (!mdns.begin("esp8266", WiFi.localIP())) {
          Serial.println("Error setting up MDNS responder!");
          while(1) { 
            delay(1000);
          }
        }
        Serial.println("mDNS responder started");
        // Start the server
        server.begin();
        Serial.println("Server started");   
        int b = 20;
        int c = 0;
        while(b == 20) { 
           b = mdns1(webtype);
    
           //If a new SSID and Password were sent, close the AP, and connect to local WIFI
           if (newSSID == true){
              newSSID = false;
    
              //convert SSID and Password sting to char
              char ssid[rsid.length()];
              rsid.toCharArray(ssid, rsid.length());         
              char pass[rpass.length()];
              rpass.toCharArray(pass, rpass.length());
    
              Serial.println("Connecting to local Wifi");
              WiFi.disconnect();
              delay(500);
        
              WiFi.begin(ssid,pass);
              delay(1000);
              if ( testWifi()) {
                Blynk.config(auth);
                return;
              }
    
             else{
                Serial.println("");
                Serial.println("New SSID or Password failed. Reconnect to server, and try again.");
                setupAP();
                return;
             }
           }
         }
    }
    
    
    void setupAP(void) {
      
      WiFi.mode(WIFI_STA);
      WiFi.disconnect();
      delay(100);
      int n = WiFi.scanNetworks();
      Serial.println("scan done");
      if (n == 0)
        Serial.println("no networks found");
      else
      {
        Serial.print(n);
        Serial.println(" networks found");
      }
      Serial.println(""); 
      st = "<ul>";
      for (int i = 0; i < n; ++i)
        {
          // Print SSID and RSSI for each network found
          st += "<li>";
          st +=i + 1;
          st += ": ";
          st += WiFi.SSID(i);
          st += " (";
          st += WiFi.RSSI(i);
          st += ")";
          st += (WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*";
          st += "</li>";
        }
      st += "</ul>";
      delay(100);
      WiFi.softAP(APssid);
      Serial.println("softAP");
      Serial.println("");
      launchWeb(1);
    }
    
    
    String urldecode(const char *src){ //fix encoding
      String decoded = "";
        char a, b;
        
      while (*src) {     
        if ((*src == '%') && ((a = src[1]) && (b = src[2])) && (isxdigit(a) && isxdigit(b))) {      
          if (a >= 'a')
            a -= 'a'-'A';       
          if (a >= 'A')                
            a -= ('A' - 10);                   
          else               
            a -= '0';                  
          if (b >= 'a')                
            b -= 'a'-'A';           
          if (b >= 'A')                
            b -= ('A' - 10);            
          else                
            b -= '0';                        
          decoded += char(16*a+b);            
          src+=3;        
        } 
        else if (*src == '+') {
          decoded += ' ';           
          *src++;       
        }  
        else {
          decoded += *src;           
          *src++;        
        }    
      }
      decoded += '\0';        
      return decoded;
    }
    
    
    int mdns1(int webtype){
      // Check for any mDNS queries and send responses
      mdns.update();
      
      // Check if a client has connected
      WiFiClient client = server.available();
      if (!client) {
        return(20);
      }
      Serial.println("");
      Serial.println("New client");
    
      // Wait for data from client to become available
      while(client.connected() && !client.available()){
        delay(1);
       }
      
      // Read the first line of HTTP request
      String req = client.readStringUntil('\r');
      
      // First line of HTTP request looks like "GET /path HTTP/1.1"
      // Retrieve the "/path" part by finding the spaces
      int addr_start = req.indexOf(' ');
      int addr_end = req.indexOf(' ', addr_start + 1);
      if (addr_start == -1 || addr_end == -1) {
        Serial.print("Invalid request: ");
        Serial.println(req);
        return(20);
       }
      req = req.substring(addr_start + 1, addr_end);
      Serial.print("Request: ");
      Serial.println(req);
      client.flush(); 
      String s;
      if ( webtype == 1 ) {
          if (req == "/")
          {
            IPAddress ip = WiFi.softAPIP();
            String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
            s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>Hello from ESP8266 at ";
            s += ipStr;
            s += "<p>";
            s += st;
            s += "<form method='get' action='a'><label>SSID: </label><input name='ssid' length=32><input name='pass' length=64><input type='submit'></form>";
            s += "</html>\r\n\r\n";
            Serial.println("Sending 200");
          }
          else if ( req.startsWith("/a?ssid=") ) {
    
            newSSID = true;
            String qsid; //WiFi SSID 
            qsid = urldecode(req.substring(8,req.indexOf('&')).c_str()); //correct coding for spaces as "+"
            Serial.println(qsid);
            Serial.println("");
            rsid = qsid;
            
            String qpass; //Wifi Password
            qpass = urldecode(req.substring(req.lastIndexOf('=')+1).c_str());//correct for coding spaces as "+"
            Serial.println(qpass);
            Serial.println("");
            rpass = qpass;
     
            s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>Hello from ESP8266 ";
            s += "<p> New SSID and Password accepted</html>\r\n\r\n"; 
          }
          else
          {
            s = "HTTP/1.1 404 Not Found\r\n\r\n";
            Serial.println("Sending 404");
          }
      } 
      else
      {
          if (req == "/")
          {
            s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>Hello from ESP8266";
            s += "<p>";
            s += "</html>\r\n\r\n";
            Serial.println("Sending 200");
          }
          else
          {
            s = "HTTP/1.1 404 Not Found\r\n\r\n";
            Serial.println("Sending 404");
          }       
      }
      client.print(s);
      Serial.println("Done with client");
      return(20);
    }
    
    
    void loop() {
      // put your main code here, to run repeatedly:
    
      Blynk.run();
    }
