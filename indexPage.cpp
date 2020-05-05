#include "indexPage.h"

indexPage::indexPage(String Ip){

  mainPage = R"=====(
    <html>

    <head>
    
      <meta name="viewport" content="width=device-width, user-scalable=no">
    
      <Title>Cameron</Title>
    
      <style>
        body {
          margin: 0;
          background-color: #F1EDEE;
        }
    
        h1 {
          margin: 3%;
          text-align: center;
          color: #000000;
          background-color: #8AA29E;
        }
    
        h2 {
          margin: 2%;
          padding: 0;
          font-weight: normal;
          font-size: 90%;
        }
    
        h3 {
          font-weight: normal;
          font-size: 90%;
          margin: 1%;
        }
    
        button.ligar {
          border: 0;
          line-height: 150%;
          height: 7%;
          width: 30%;
          background-color: #686963;
          color: FFFFFF;
          margin-left: 1%;
        }
    
        button.desligar {
          border: 0;
          line-height: 150%;
          height: 7%;
          width: 30%;
          background-color: #DB5461;
          color: FFFFFF;
          margin-left: 1%;
        }
    
        a.rodape {
          margin-right: 1%;
          float: right;
          height: 4%;
          background-color: #686963;
          border: 0;
          color: #FFFFFF;
          width: 20%;
          text-align: center;
          text-decoration: none;
        }
    
        p {
          margin: 0;
          margin-top: 2%;
        }
    
        input {
          margin-left: 3%;
          width: 50%;
          background-color: EEE4E1;
        }
    
        .slider {
          -webkit-appearance: none;
          width: 200;
          height: 4%;
          border-radius: 4%;
          background: #F1EDEE;
          outline: none;
          opacity: 0.7;
          -webkit-transition: .2s;
          transition: opacity .2s;
        }
            
            .slider::-moz-range-thumb {
              width: 20px;
            height: 20px;
            background: #686963;
            cursor: pointer;
        }
    
        aside {
          background-color: #8AA29E;
          padding: 1%;
          margin: 3%;
        }
      </style>
    </head>
    
    <body  onload="carregarPagina()">
      <form method="GET" id="form">
        <input type="hidden" name="function" id="function" />
      </form>
      <h1> Cameron </h1>
    
      <aside>
    
        <h2>Terminal 1</h2>
    
        <button class="ligar" onclick="acionarLigar(1)">Ligar</button>
    
        <input type="range" min="0" max="100" value="100" class="slider" id="range1" name="input1" onchange="atualizarLigar(1)">
    
        <p>
          <button class="desligar" onclick="acionarDesligar(1)">Desligar</button>
        </p>
    
      </aside>
      <aside>
    
        <h2>Terminal 2</h2>
    
        <button class="ligar" onclick="acionarLigar(2)">Ligar</button>
    
        <input type="range" min="0" max="100" value="100" class="slider" id="range2" name="input2" onchange="atualizarLigar(2)">
    
        <p>
          <button class="desligar" onclick="acionarDesligar(2)">Desligar</button>
        </p>
    
      </aside>
      <aside>
    
        <h2>Terminal 3</h2>
    
        <button class="ligar" onclick="acionarLigar(3)">Ligar</button>
    
        <input type="range" min="0" max="100" value="100" class="slider" id="range3" name="input3" onchange="atualizarLigar(3)">
    
        <p>
          <button class="desligar" onclick="acionarDesligar(3)">Desligar</button>
        </p>
    
      </aside>
      <aside>
        <h3> SSID:
          <input id='ssid' />
          <a href="" onclick="conectar()" id='conectar' class="rodape">Conectar</a>
        </h3>
        <h3> PWD:
          <input id='pwd' />
          <a href="" id='sair' onclick="sair()" class="rodape">Sair</a>
        </h3>
      </aside>
      <script>
        prefixos = ['01234567001', '01234567002', '01234567003'];
        ranges = function () {
          return [document.getElementById('range1'), document.getElementById('range2'), document.getElementById('range3')];
        };
        function acionarDesligar(indice){
          let i = indice - 1;
          ranges()[i].value = 0;
          atualizarLigar(indice);
        }
        function acionarLigar(indice){
          let i = indice - 1;
          ranges()[i].value = 100;
          atualizarLigar(indice);
        }
        function atualizarLigar(indice) {
          let i = indice - 1;
          let range = ranges()[i].value;
          let funcao = document.getElementById("function");
          let prefixo = prefixos[i];
          funcao.setAttribute("value", prefixo + (range >= 100 ? range : range >= 10 ? "0" + range : "00" + range));
          document.getElementById("form").submit();
        };
        let carregarPagina = function () {
            let valor = pegarParametro('function'); 
            if(valor){
              if(valor.indexOf("&") != 0)
              {
                document.getElementById('range'+valor.substring(valor.length-4, valor.length-3)).value = +valor.substring(valor.length-3, valor.length);
              }else{
                let texto = valor.split("*");
                document.getElementById('ssid').value = texto[0].split("&")[1];
                document.getElementById('pwd').value = texto[1].split("%")[0];
              }
            }
        };
        function pegarParametro(nomeParametro) {
          var result = null,
            tmp = [];
          var items = [location.search.substr(1)];
          for (var index = 0; index < items.length; index++) {
            tmp = items[index].split("=");
            if (tmp[0] === nomeParametro) result = (tmp[1]);
          }
          return result;
        }
        function conectar() {
                let conectar = document.getElementById('conectar');
              let ssid = document.getElementById('ssid').value ? "&"+document.getElementById('ssid').value : '';
              let pwd = ssid && document.getElementById('pwd') ? '*'+document.getElementById('pwd').value : '';
              let url = document.location.href.split("?")[0]+"?function="+ssid+pwd+"%";
              conectar.setAttribute('href', url);
        };
        function sair() {
          document.getElementById('sair').setAttribute('href', document.location.href + "/&sair%");
        };
      </script>
    </body>
    
  </html>
    
  )=====";
}

String indexPage::getPage(){
  return mainPage;
}
