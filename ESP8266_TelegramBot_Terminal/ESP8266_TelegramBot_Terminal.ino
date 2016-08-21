/***********************************************************************************************************/
/* El programa representa a un Bot que hace de terminal entrada/salida de datos (como si de el terminal    */
/* serie se tratase) para ello, se implementan las funciones correspondientes a read() y println().        */
/* En este caso, se envian los datos de lectura del pin analogico A0 del esp8266 (Sketch AnalogRead).      */
/*                                                                                                         */
/* Nota: Para inicializar el control del bot se necesita su ID de chat, por ello el usuario ha de enviar   */
/* cualquier texto, en primera instancia, para que comience a funcionar el terminal (el programa estara    */
/* bloqueado en telegram_begin() mientras tanto).                                                          */
/*                                                                                                         */
/* Se precisan las siguientes librerías:                                                                   */
/* UniversalTelegramBot: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot                    */
/* ArduinoJson: Buscarla con Arduino IDE en Programa/Incluir libreria/Gestionar librerias                  */
/***********************************************************************************************************/
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

/***********************************************************************************************************/

// Parametros de conexion al Punto de Acceso
char ssid[] = "xxxxxxxxxxxxxxxxxxxxxx"; // A establecer por el usuario
char pass[] = "yyyyyyyy"; // A establecer por el usuario

// Token del BOT de Telegram (crear bot con botfather)
#define BOTtoken "XXXXXXXXX:XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" // A establecer por el usuario (consultar mediante botFather)

/***********************************************************************************************************/

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int sensorValue;

/***********************************************************************************************************/

void setup()
{
    Serial.begin(115200);
    wifi_begin();
    telegram_begin();
}

void loop()
{
    // AnalogRead
    sensorValue = analogRead(A0);
    telegram_println(String(sensorValue));

    /*
    // Echo Test
    telegram_println(telegram_read());
    delay(10);
    */
}

void telegram_begin() // Necesario para determinar el chat id del bot
{
    long Bot_lasttime;
    int Bot_mtbs = 1000; // Tiempo entre lecturas de mensajes 1s
    bool start = false;

    while(start == false)
    {
        // El tiempo para consultar si hay mensajes nuevos ha transcurrido
        if (millis() > Bot_lasttime + Bot_mtbs)
        {
            int numNewMessages = bot.getUpdates(bot.last_message_recived + 1);
            if(numNewMessages)
            {
                start = true;
                Serial.println("Telegram begin success");
            }
            Bot_lasttime = millis();
        }
    }
}

void telegram_println(String msg)
{
    if(msg != "")
        bot.sendSimpleMessage(bot.messages[0].chat_id, msg, "");
}

String telegram_read()
{
    String msg = "";

    if(bot.getUpdates(bot.last_message_recived + 1))
        msg = bot.messages[0].text;

    return msg;
}

void wifi_begin()
{
    // Reinicia la interfaz de conexion en caso de que estubiera conectado a una red
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(1000);
    
    // Conexion a la red
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);
    
    // Esperar la conexión
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    // Conectado a la red
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    IPAddress ip = WiFi.localIP();
    Serial.println(ip);
}

