#include <Arduino.h> 
#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"
#include "driver/gpio.h"
#include "esp_rom_sys.h"

// --- Configurações Wi-Fi ---
const char* ssid = "SEU_SSID"; 
const char* password = "SUA_SENHA";        
const int wifi_channel = 6;

// --- Definições de Pinos e Tipos ---
#define DHTPIN 2       
#define DHTTYPE DHT22  
#define SERVO_PIN 26   

// --- Definições de Limiares ---
const float TEMPERATURA_QUENTE = 28.0; 
const float UMIDADE_BAIXA = 60.0;      
const float TEMPERATURA_BAIXA = 20.0;  
const float UMIDADE_ALTA = 80.0;       

// Variável de estado: 0 = Fechado, 1 = Aberto
int estadoVaral = 0; 
bool controleManual = false;

// Variáveis de Simulação: Usadas para garantir que a lógica AUTO mude o estado.
float sim_t = 25.0; // Temperatura simulada
float sim_h = 70.0; // Umidade simulada

// Inicialização do Servidor Web na porta 80
WebServer server(8080);

// Inicialização do Sensor DHT (Dummy, pois a leitura será simulada)
DHT dht(DHTPIN, DHTTYPE);


// --- FUNÇÃO DE CONTROLE DO SERVO  ---
void servo_set_angle(int angle)
{
    // Esta função será executada, mas como o servo não está conectado, não fará nada.
    int min_us = 500;
    int max_us = 2400;
    int pulse = min_us + (angle * (max_us - min_us) / 180);

    gpio_set_level((gpio_num_t)SERVO_PIN, 1);
    esp_rom_delay_us(pulse);
    gpio_set_level((gpio_num_t)SERVO_PIN, 0);
    esp_rom_delay_us(20000 - pulse); 
}

// --- FUNÇÕES DA API  ---

String obterEstadoVaral() {
    if (controleManual) {
        return "Manual - " + String(estadoVaral == 1 ? "ABERTO" : "FECHADO");
    }
    return estadoVaral == 1 ? "Automático - ABERTO (Sol)" : "Automático - FECHADO (Chuva)";
}

// ROTA /readings: Envia dados (T e H simulados, S real) via JSON
void handleReadings() {
    String jsonResponse = "{\"T\": " + String(sim_t) + 
                          ", \"H\": " + String(sim_h) + 
                          ", \"S\": \"" + obterEstadoVaral() + "\"}";
                          
    server.send(200, "application/json", jsonResponse);
}

// ROTA /toggle: Recebe o comando para alternar o modo Manual/Automático
void handleToggle() {
    controleManual = !controleManual;

    if (controleManual) {
        // Entrou em manual: inverte o estado para dar feedback (e simula movimento)
        estadoVaral = (estadoVaral == 1) ? 0 : 1; 
        int angle = (estadoVaral == 1) ? 90 : 0;
        servo_set_angle(angle);
        Serial.println(">>> Modo MANUAL ATIVADO. Varal sim. movido para " + String(angle));
    } else {
        Serial.println(">>> Modo MANUAL DESATIVADO. Retornando ao controle automático.");
    }
    
    server.send(200, "text/plain", "Toggle successful"); 
}

void handleRoot() {
    server.send(200, "text/plain", "API do Varal Automatico ESP32 esta online.");
}

// --- SETUP e LOOP ---

void setup() {
    Serial.begin(115200);
    
    pinMode(SERVO_PIN, OUTPUT); 
    servo_set_angle(0); // Posição inicial: FECHADO

    dht.begin();

    // Conexão Wi-Fi (usando o método robusto)
    Serial.print("Conectando a ");
    Serial.println(ssid);
    
    WiFi.begin(ssid, password);
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 30) {
        delay(1000); 
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi Conectado com SUCESSO!");
        Serial.print("Endereço IP: ");
        Serial.println(WiFi.localIP());

        server.on("/", HTTP_GET, handleRoot);
        server.on("/readings", HTTP_GET, handleReadings);
        server.on("/toggle", HTTP_GET, handleToggle);
        server.begin();
        Serial.println("HTTP server iniciado.");
    } else {
        Serial.println("\nFalha na Conexao Wi-Fi.");
    }
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        server.handleClient(); 
    }

    // --- LÓGICA DE CONTROLE AUTOMÁTICO SIMULADA ---
    if (!controleManual) {
        // Simula a mudança de clima a cada 10 segundos (para ver o site mudar)
        static unsigned long lastChange = 0;
        if (millis() - lastChange > 10000) { 
            // Alterna entre CLIMA QUENTE (30T/50H) e CLIMA CHUVOSO (18T/85H)
            if (estadoVaral == 0) {
                sim_t = 30.5; // Quente
                sim_h = 50.0; // Seco
            } else {
                sim_t = 18.0; // Frio
                sim_h = 85.0; // Úmido
            }
            lastChange = millis();
        }

        // LÓGICA DE DETECÇÃO (usando variáveis simuladas)
        
        // 1. CLIMA QUENTE / SOL (Varal Aberto: 90°)
        if (sim_t > TEMPERATURA_QUENTE && sim_h < UMIDADE_BAIXA) {
            if (estadoVaral != 1) { 
                servo_set_angle(90); 
                estadoVaral = 1;
                Serial.println("Auto: ABRINDO VARAL.");
            }
        } 
        
        // 2. CLIMA CHUVOSO (Varal Fechado: 0°)
        else if (sim_t < TEMPERATURA_BAIXA && sim_h > UMIDADE_ALTA) {
            if (estadoVaral != 0) { 
                servo_set_angle(0); 
                estadoVaral = 0;
                Serial.println("Auto: FECHANDO VARAL.");
            }
        } 
    }
    delay(10); 
}