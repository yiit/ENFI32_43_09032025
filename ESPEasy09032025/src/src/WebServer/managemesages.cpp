#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include "../WebServer/manageproducts.h"
#include "../WebServer/common.h"
#include "../WebServer/HTML_wrappers.h"
#include "../WebServer/ESPEasy_WebServer.h"
#include "../Helpers/ESPEasy_Storage.h"
#include "../WebServer/Markup.h"
#include "../WebServer/Markup_Buttons.h"

void handle_managemesages() {
  if (!isLoggedIn()) return;
  if (!isLisansIn()) return;

  TXBuffer.startStream();
  sendHeadandTail_stdtemplate(_HEAD);

  addHtml(F(R"rawliteral(
<style>
body { font-family: Arial, sans-serif; padding: 20px; background: #f4f4f4; }
h3 { margin-top: 30px; background: #dff9fb; padding: 10px; border-radius: 5px; display: flex; justify-content: space-between; align-items: center; }
table { width: 100%; border-collapse: collapse; margin-top: 10px; background: white; }
th, td { border: 1px solid #ccc; padding: 8px; font-size: 15px; }
tr:nth-child(even) { background: #f7f7f7; }
tr:hover { background: #dcdde1; }
input[type="text"] { width: 95%; padding: 5px; }
input.limit-warning { border-color: red !important; box-shadow: 0 0 4px red; }
td.baslik-ozel { background: #ffeaa7 !important; text-align: center; font-weight: bold; }
button.reset, button.saveAll, button.olustur {
  padding: 6px 10px; margin: 3px;
  border: none; border-radius: 4px; cursor: pointer;
}
button.reset { background: #e74c3c; color: white; }
button.saveAll { background: #0984e3; color: white; margin-bottom: 20px; }
button.olustur { background: #2ecc71; color: white; font-size: 14px; }
</style>

<h2>📝 Tüm Mesaj Grupları</h2>
<button class='saveAll' onclick='hepsiniKaydet()'>💾 Hepsini Kaydet</button>
<div id="mesajContainer"></div>

<script>
let mesajlar = [];
let eksikGruplar = [];

function mesajSatiri(grup, i, deger) {
  const isBaslik = (i === 0);
  return `<tr>
    <td>${i}</td>
    <td class='${isBaslik ? "baslik-ozel" : ""}'>
      <input type='text' id='msg_${grup}_${i}' value='${deger.replace(/'/g,"&#39;")}' oninput='karakterKontrol(this)' >
    </td>
    <td>${!isBaslik ? `<button class='reset' onclick='sifirla(${grup},${i})'>🗑️</button>` : ""}</td>
  </tr>`;
}

function karakterKontrol(input) {
  if (input.value.length > 32) {
    input.classList.add("limit-warning");
    alert("⛔ En fazla 32 karakter girilebilir!");
    input.value = input.value.slice(0, 32);
  } else {
    input.classList.remove("limit-warning");
  }
}

function tabloCiz() {
  let html = "";
  for (let grupIndex = 0; grupIndex < 8; grupIndex++) {
    const grup = mesajlar[grupIndex];
    const eksik = eksikGruplar.includes(grupIndex);

    html += `<h3>
      📂 mesaj_${grupIndex}.json 
      ${!eksik ? `<strong>${grup[0]}</strong>` : "<span style='color:red;'>⛔ Eksik</span>"}
      ${eksik ? `<button class='olustur' onclick='olusturDosya(${grupIndex})'>📄 Oluştur</button>` : ""}
    </h3>`;

    if (eksik) continue;

    html += "<table><thead><tr><th>#</th><th>Mesaj</th><th>İşlem</th></tr></thead><tbody>";
    for (let i = 0; i < grup.length; i++) {
      html += mesajSatiri(grupIndex, i, grup[i]);
    }
    html += "</tbody></table>";
  }

  document.getElementById('mesajContainer').innerHTML = html;
}

function sifirla(grup, i) {
  mesajlar[grup][i] = "Mesaj" + i;
  tabloCiz();
}

function hepsiniKaydet() {
  for (let g = 0; g < mesajlar.length; g++) {
    if (eksikGruplar.includes(g)) continue;
    for (let i = 0; i < mesajlar[g].length; i++) {
      const el = document.getElementById(`msg_${g}_${i}`);
      if (el) mesajlar[g][i] = el.value.trim().slice(0, 32);
    }
  }

  fetch('/savemesajlar', {
    method: 'POST',
    headers: {'Content-Type':'application/json'},
    body: JSON.stringify({veri: mesajlar})
  }).then(r=>r.text()).then(t=>{
    alert("✅ Tüm mesajlar kaydedildi!");
  });
}

function olusturDosya(g) {
  fetch(`/olusturmesaj?grup=${g}`)
    .then(() => location.reload());
}

window.addEventListener('DOMContentLoaded', () => {
)rawliteral"));

  // Backend'de JSON'ları oku
  addHtml(F("mesajlar = []; eksikGruplar = [];"));
  for (int i = 0; i < 8; i++) {
    String path = "/mesaj_" + String(i) + ".json";
    File f = tryOpenFile(path.c_str(), "r");
    if (f) {
      DynamicJsonDocument doc(2048);
      DeserializationError err = deserializeJson(doc, f);
      f.close();
      if (!err && doc["mesaj"].is<JsonArray>()) {
        String jsonStr;
        serializeJson(doc["mesaj"], jsonStr);
        addHtml("mesajlar[" + String(i) + "] = " + jsonStr + ";");
      } else {
        addHtml("mesajlar[" + String(i) + "] = []; eksikGruplar.push(" + String(i) + ");");
      }
    } else {
      addHtml("mesajlar[" + String(i) + "] = []; eksikGruplar.push(" + String(i) + ");");
    }
  }
  addHtml(F("tabloCiz(); });</script>"));

  sendHeadandTail_stdtemplate(_TAIL);
  TXBuffer.endStream();
}

void handle_savemesages() {
  if (!web_server.hasArg("plain")) {
    web_server.send(400, "text/plain", "Eksik veri");
    return;
  }

  DynamicJsonDocument body(8192);
  DeserializationError err = deserializeJson(body, web_server.arg("plain"));
  if (err) {
    web_server.send(400, "text/plain", "JSON parse hatası");
    return;
  }

  JsonArray veri = body["veri"].as<JsonArray>();
  for (int i = 0; i < veri.size(); i++) {
    String path = "/mesaj_" + String(i) + ".json";
    File file = LittleFS.open(path, "w");
    if (file) {
      DynamicJsonDocument grupDoc(1024);
      grupDoc["mesaj"] = veri[i];
      serializeJson(grupDoc, file);
      file.close();
    }
  }

  web_server.send(200, "text/plain", "Kayıt başarılı");
}



void handle_newmesages() {
  if (!web_server.hasArg("grup")) return;
  int grup = web_server.arg("grup").toInt();
  if (grup < 0 || grup > 7) return;

  String path = "/mesaj_" + String(grup) + ".json";
  File file = LittleFS.open(path, "w");
  if (file) {
    DynamicJsonDocument doc(2048);
    JsonArray arr = doc.createNestedArray("mesaj");

    arr.add("GRUP" + String(grup)); // başlık
    for (int i = 1; i < 30; i++) {  // 29 adet mesaj
      arr.add("Mesaj" + String(i));
    }

    serializeJson(doc, file);
    file.close();
  }

  web_server.send(200, "text/plain", "OK");
}
