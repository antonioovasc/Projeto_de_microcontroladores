<h1>🛠️ Projetos de Microcontroladores</h1>

<p>
  Bem-vindo ao repositório <strong>Projetos de Microcontroladores</strong>!<br>
  Este repositório reúne uma coleção de projetos desenvolvidos com microcontroladores, utilizando simulações e prototipagem no <strong>Wokwi</strong>.<br>
  O objetivo é centralizar, organizar e facilitar o acesso aos projetos, além de permitir expansão futura com novos links.
</p>

<hr>

<h2>📂 Índice de Projetos</h2>

<h3>🔹 1. Porta com Sensor de Proximidade</h3>
<p>
  Simulação de uma porta automática que utiliza um sensor de proximidade para detectar a presença de objetos/pessoas e acionar uma porta.<br>
  🔗 <strong>Acessar projeto:</strong> 
  <a href="https://wokwi.com/projects/448620777839790081">https://wokwi.com/projects/448620777839790081</a>
</p>

<hr>

<h3>🔹 2. Varal Automático</h3>
<p>
  Um sistema automatizado que recolhe roupas de um varal com base na detecção de chuva ou controle programado.<br>
  🔗 <strong>Acessar projeto:</strong> 
  <a href="https://wokwi.com/projects/448679863058845697">https://wokwi.com/projects/448679863058845697</a>
</p>

<hr>

<h2>🎥 Vídeo Explicativo dos Projetos</h2>
<p>
  Para uma explicação detalhada dos projetos apresentados, assista ao vídeo no link abaixo:<br>
  🔗 <strong>Acessar vídeo:</strong>
  <a href="https://drive.google.com/file/d/1Aau1jqP2Rd85IPOpbl81hUDn7mr385n-/view?usp=sharing">
    Clique aqui para assistir
  </a>
</p>

<hr>

<h2>📑 Slide de Apresentação</h2>
<p>
  Acesse o slide utilizado para apresentar os projetos:<br>
  🔗 <strong>Acessar slide:</strong>
  <a href="https://www.canva.com/design/DAG5hpgmfGE/KsJTqV66D9We7qD5q3i_Xg/edit?utm_content=DAG5hpgmfGE&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton">
    Clique aqui para visualizar o slide
  </a>
</p>

<hr>

<h2>📘 Roteiro Completo — Varal Automático com ESP32</h2>
<p>
  Guia passo a passo: do ambiente ao funcionamento total do sistema.<br>
  Este roteiro detalha todo o processo para montar, programar e testar o projeto 
  <strong>Varal Automático com ESP32</strong>, incluindo código, interface web, comunicação via API e validações.
</p>

<hr>

<h2>🧰 Seção 1 — Preparando o Ambiente (Arduino IDE)</h2>
<ol>
  <li>
    <strong>Instalar o Arduino IDE</strong><br>
    Baixe e instale a versão mais recente.
  </li>
  <br>

  <li>
    <strong>Adicionar suporte ao ESP32</strong><br>
    Vá em: <em>Arquivo &gt; Preferências</em><br>
    No campo <em>URL de Gerenciador de Placas</em>, adicione:<br>
    <code>https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json</code><br><br>

    Agora vá em: <em>Ferramentas &gt; Placa &gt; Gerenciador de Placas...</em><br>
    Pesquise por <strong>esp32</strong> e instale <strong>esp32 by Espressif Systems</strong>.
  </li>
  <br>

  <li>
    <strong>Instalar biblioteca DHT (Adafruit)</strong><br>
    Vá em: <em>Sketch &gt; Incluir Biblioteca &gt; Gerenciar Bibliotecas...</em><br>
    Procure por <strong>DHT</strong> e instale <strong>DHT sensor library by Adafruit</strong>.
  </li>
</ol>

<hr>

<h2>🧠 Seção 2 — Código do ESP32 (Lógica Inteligente)</h2>
<ol>
  <li>
    <strong>Colar o código principal</strong><br>
    Abra um novo sketch no Arduino IDE e cole o código final do projeto.
  </li>
  <br>

  <li>
    <strong>Configurar Wi-Fi</strong><br>
    Localize no código:<br>
    <code>
      const char* ssid = "SEU_WIFI";<br>
      const char* password = "SUA_SENHA";
    </code><br>
    Substitua pelos dados reais da sua rede.
  </li>
  <br>

  <li>
    <strong>Selecionar placa e porta</strong><br>
    • <em>Ferramentas &gt; Placa</em>: escolha <strong>ESP32 Dev Module</strong><br>
    • Conecte o ESP32 via USB<br>
    • Selecione a porta correta em <em>Ferramentas &gt; Porta</em>
  </li>
  <br>

  <li>
    <strong>Velocidade de Upload</strong><br>
    Configure para <strong>115200</strong>.
  </li>
  <br>

  <li>
    <strong>Fazer upload do código</strong><br>
    Clique em <em>Upload</em>.<br>
    Durante o <code>Connecting...</code>, segure o botão <strong>BOOT/FLASH</strong>, pressione e solte <strong>EN/RST</strong> e então solte BOOT quando iniciar o upload.
  </li>
</ol>

<hr>

<h2>🌐 Seção 3 — Descobrindo o IP do ESP32</h2>
<ol>
  <li>Abrir o <strong>Monitor Serial</strong></li>
  <li>Configurar para <strong>115200 baud</strong></li>
  <li>Pressionar o botão <strong>EN/RST</strong></li>
  <li>
    Procurar a mensagem:<br>
    <code>
      WiFi Conectado com SUCESSO!<br>
      Endereço IP: 192.168.x.x
    </code><br>
    Anote o IP (porta: <strong>8080</strong>).
  </li>
</ol>

<hr>

<h2>🖥️ Seção 4 — O Site (Interface Web de Controle)</h2>

<ol>
  <li>
    <strong>Criar o arquivo HTML</strong><br>
    Copie o código HTML/JavaScript do projeto.
  </li>
  <br>

  <li>
    <strong>Configurar IP do ESP32 no HTML</strong><br>
    Localize:<br>
    <code>const ESP32_IP = "http://SEU_IP_AQUI";</code><br><br>

    Substitua por algo como:<br>
    <code>http://192.168.15.24:8080</code>
  </li>
  <br>

  <li>
    Salve como <strong>varal.html</strong>
  </li>
</ol>

<hr>

<h2>🔄 Seção 5 — Fazendo o Site e ESP32 Conversarem (Servidor Local)</h2>
<ol>
  <li>Certifique-se de que o <strong>Python</strong> está instalado.</li>
  <br>

  <li>
    Abrir terminal e ir até a pasta do arquivo:<br>
    <code>cd pasta/do/arquivo</code>
  </li>
  <br>

  <li>
    Iniciar servidor local:<br>
    <code>python -m http.server 8000</code>
  </li>
  <br>

  <li>
    Abrir no navegador:<br>
    <code>http://localhost:8000/varal.html</code>
  </li>
</ol>

<hr>

<h2>✔️ Seção 6 — Testando e Validando Tudo</h2>

<h3>1. Exibição dos Dados</h3>
<p>
  O site deve exibir:<br>
  • Temperatura 🌡️<br>
  • Umidade 💧<br>
  • Estado atual (ABERTO/FECHADO)
</p>

<h3>2. Teste de Controle Manual</h3>
<p>
  Clique em <strong>Assumir Controle Manual</strong> para liberar o botão de ação.
</p>

<h3>3. Validação no Monitor Serial</h3>
<p>
  Você deve ver logs como:<br>
  <code>
    Modo MANUAL ATIVADO<br>
    Auto: ABRINDO VARAL
  </code><br>
  Isso confirma a comunicação correta entre site e ESP32.
</p>
