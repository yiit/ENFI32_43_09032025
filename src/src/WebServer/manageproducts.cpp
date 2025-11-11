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

void handle_urunler() {
  if (!isLoggedIn()) return;
  if (!isLisansIn()) return;

  TXBuffer.startStream();
  sendHeadandTail_stdtemplate(_HEAD);


  addHtml(F(R"rawliteral(
  <script src="https://cdnjs.cloudflare.com/ajax/libs/jspdf/2.5.1/jspdf.umd.min.js"></script>
  <style>
  :root {
    --primary:#007bff; --primary-dark:#0056b3;
    --success:#28a745; --success-dark:#1e7e34;
    --danger:#dc3545; --danger-dark:#a71d2a;
    --border:#ccc; --bg:#fafafa; --box-bg:#fff; --text:#333;
  }
  @media (prefers-color-scheme: dark){
    :root {
      --primary:#4dabf7; --primary-dark:#228be6;
      --success:#51cf66; --success-dark:#37b24d;
      --danger:#ff6b6b; --danger-dark:#fa5252;
      --border:#444; --bg:#1e1e1e; --box-bg:#2b2b2b; --text:#eee;
    }
  }
  body{font-family:'Segoe UI',Arial,sans-serif;margin:20px;background:var(--bg);color:var(--text);}
  form#productForm{display:flex;flex-wrap:wrap;gap:16px;align-items:flex-end;margin-bottom:20px;
  background:var(--box-bg);padding:15px;border-radius:8px;box-shadow:0 2px 6px rgba(0,0,0,0.1);}
  form#productForm label{display:flex;flex-direction:column;font-weight:600;font-size:15px;color:var(--text);flex:1;min-width:150px;}
  form#productForm input,form#productForm select{padding:10px 12px;border:1px solid var(--border);border-radius:6px;font-size:15px;margin-top:4px;background:var(--box-bg);color:var(--text);}
  form#productForm input:focus,form#productForm select:focus{border-color:var(--primary);outline:none;box-shadow:0 0 6px rgba(0,123,255,0.6);}
  form#productForm button{background:var(--primary);color:#fff;border:none;border-radius:6px;padding:10px 16px;font-size:16px;cursor:pointer;margin-top:22px;display:flex;align-items:center;gap:6px;flex-shrink:0;}
  form#productForm button:hover{background:var(--primary-dark);}
  #searchExport{display:flex;flex-wrap:wrap;gap:10px;margin-bottom:15px;}
  #searchInput{padding:10px 12px;border:1px solid var(--border);border-radius:6px;font-size:15px;width:220px;background:var(--box-bg);color:var(--text);}
  #searchInput:focus{border-color:var(--primary);outline:none;box-shadow:0 0 6px rgba(0,123,255,0.6);}
  #exportBtn,#pdfBtn,#bulkDeleteBtn{background:var(--success);color:#fff;border:none;border-radius:6px;padding:10px 14px;font-size:15px;cursor:pointer;display:inline-flex;align-items:center;gap:6px;}
  #pdfBtn{background:#6c5ce7;} #pdfBtn:hover{background:#4834d4;}
  #bulkDeleteBtn{background:var(--danger);} #bulkDeleteBtn:hover{background:var(--danger-dark);}
  #urunTablo{border-collapse:collapse;width:100%;background:var(--box-bg);border-radius:8px;overflow:hidden;box-shadow:0 2px 6px rgba(0,0,0,0.1);margin-bottom:10px;}
  #urunTablo th,#urunTablo td{padding:12px 10px;text-align:left;font-size:15px;color:var(--text);}
  #urunTablo th{background:rgba(0,0,0,0.05);cursor:pointer;}
  #urunTablo tbody tr:nth-child(odd){background:var(--box-bg);}
  #urunTablo tbody tr:nth-child(even){background:rgba(0,0,0,0.02);}
  #urunTablo tbody tr:hover{background:var(--primary);color:#fff;transition:background 0.2s;}
  button.action{padding:8px 12px;border:none;border-radius:6px;cursor:pointer;font-size:14px;margin-right:6px;display:inline-flex;align-items:center;gap:6px;}
  button.edit{background:var(--success);color:#fff;}button.edit:hover{background:var(--success-dark);}
  button.delete{background:var(--danger);color:#fff;}button.delete:hover{background:var(--danger-dark);}
  #mesaj{margin-top:12px;font-weight:bold;font-size:16px;color:var(--success);}
  .pagination{display:flex;justify-content:center;align-items:center;gap:8px;margin-top:10px;}
  .pagination button{padding:6px 10px;border:none;border-radius:4px;background:var(--primary);color:#fff;cursor:pointer;}
  .pagination button:disabled{background:#888;cursor:not-allowed;}
  .modal-bg{position:fixed;top:0;left:0;width:100%;height:100%;background:rgba(0,0,0,0.5);display:none;align-items:center;justify-content:center;z-index:9999;}
  .modal-box{background:var(--box-bg);padding:20px;border-radius:8px;text-align:center;box-shadow:0 2px 6px rgba(0,0,0,0.3);max-width:300px;color:var(--text);}
  .modal-box p{margin-bottom:15px;font-size:16px;}
  .modal-box button{margin:10px;padding:8px 12px;border:none;border-radius:4px;font-size:15px;cursor:pointer;}
  .modal-confirm{background:var(--danger);color:#fff;} .modal-cancel{background:#aaa;color:#000;}
  @media (max-width:768px){form#productForm{flex-direction:column;align-items:stretch;}form#productForm label{min-width:100%;}#searchInput{width:100%;}}
  input.limit-warning{border-color:red !important;box-shadow: 0 0 5px red;}
  </style>
  <script>
  document.addEventListener('DOMContentLoaded',function(){
    const kod=document.getElementById('kod');
    const isim=document.getElementById('isim');
    const skt=document.getElementById('skt');

    kod.addEventListener('input',()=>{
      if(kod.value.length>13){kod.value=kod.value.slice(0,13);alert('Kod en fazla 13 karakter olabilir!');}
    });
    isim.addEventListener('input',()=>{
      if(isim.value.length>48){isim.value=isim.value.slice(0,48);alert('İsim en fazla 48 karakter olabilir!');}
    });
    skt.addEventListener('input',()=>{
      if(+skt.value>700){skt.value=700;alert('SKT en fazla 700 gün olabilir!');}
      if(+skt.value<0){skt.value=0;alert('SKT en az 0 gün olabilir!');}
    });
  });
  </script>
  )rawliteral"));

  // form
  addHtml(F("<form id='productForm'>"));
  addHtml(F("<input type='hidden' id='editIndex'>"));
  addHtml(F("<label>Kod<input type='text' id='kod'></label>"));
  addHtml(F("<label>İsim<input type='text' id='isim'></label>"));
  addHtml(F("<label>Tip<select id='tip'><option value='0'>AĞIRLIK</option><option value='1'>ADET</option></select></label>"));
  addHtml(F("<label>SKT<input type='number' id='skt'></label>"));
  addHtml(F("<label>Etiket Şablonu:<select id='etiketSelect'>"));

  File root = LittleFS.open("/");
  File file = root.openNextFile();
  int i = 1;
  String etiketMapping = "const etiketDosyalari = [";

  addHtml("<option value='0'>Varsayılan</option>");
  etiketMapping += "\"Varsayılan\"";  // sadece ilk satırda eklenir

  //bool first = true;  // 🔍 virgül kontrolü için

  while (file) {
    String fname = file.name();
    if (fname.endsWith(".prn")) {
      addHtml("<option value='" + String(i) + "'>" + fname + "</option>");
      //if (first) etiketMapping += "\"Varsayılan\"";  // ❌ ilkinde virgül eklenmesin
      etiketMapping += ",\"" + fname + "\"";
      //first = false;
      i++;
    }
    file = root.openNextFile();
  }

  addHtml(F("</select></label>"));
  etiketMapping += "];";
  addHtml("<script>" + etiketMapping + "</script>");
  
  addHtml(F("<label>Dara (g)<input type='number' id='dara' step='0.001'></label>"));
  addHtml(F("<label>Birim Gramaj (g)<input type='number' id='birimGramaj' step='0.001'></label>"));
  // ✅ Barkod formatı seçenekleri eklenmeli
  addHtml(F("<label>Barkod Formatı<select id='barkodFormat'>"
          "<option value='0'>Standart</option>"
          "<option value='1'>GS1</option>"
          "<option value='2'>Özel</option>"
          "</select></label>"));

  addHtml(F("<label>Mesaj<input type='text' id='mesajInput' maxlength='32'></label>"));
  
  addHtml(F("<input type='hidden' id='etiket'>")); 
  addHtml(F("<button type='submit'>"
           "<svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 512 512' width='16' height='16' fill='currentColor'><path d='M96 0C78.3 0 64 14.3 64 32V480c0 17.7 14.3 32 32 32H416c17.7 0 32-14.3 32-32V128L352 0H96zM256 128c35.3 0 64 28.7 64 64s-28.7 64-64 64s-64-28.7-64-64s28.7-64 64-64zM128 448V352H384v96H128z'/></svg> Kaydet</button>"));
  html_end_form();

  // üst kısım
  addHtml(F("<div id='searchExport'>"));
  addHtml(F("<input type='text' id='searchInput' placeholder='🔍 Kod veya isim ara...'>"));
  addHtml(F("<button id='exportBtn'>CSV</button>"));
  addHtml(F("<button id='pdfBtn'>PDF</button>"));
  addHtml(F("<button id='bulkDeleteBtn'>Seçilileri Sil</button>"));
  addHtml(F("</div>"));

  addHtml(F("<div id='msg'></div>"));
  addHtml(F("<table id='urunTablo'><thead><tr>"
            "<th>#</th><th></th><th>Kod</th><th>İsim</th><th>Tip</th><th>SKT</th><th>Etiket</th><th>Dara</th><th>Birim Gramaj</th><th>Barkod Formatı</th><th>Mesaj</th><th>İşlem</th>"
            "</tr></thead><tbody></tbody></table><div class='pagination'><button id='prevPage'>«</button><span id='pageInfo'></span><button id='nextPage'>»</button></div>"));

  addHtml(F("<div class='modal-bg' id='deleteModal'><div class='modal-box'><p id='deleteText'></p><button class='modal-confirm' id='confirmDelete'>Evet</button><button class='modal-cancel' id='cancelDelete'>Hayır</button></div></div>"));

  File urun = tryOpenFile(F("/urun.json"), "r");
  if(urun){
    DynamicJsonDocument doc(32000);
    deserializeJson(doc, urun);
    urun.close();
    String jsonStr;serializeJson(doc,jsonStr);
    addHtml(F("<script>let data="));addHtml(jsonStr);addHtml(F(";</script>"));
  }

  addHtml(F(R"rawliteral(
<script>
let urunler=data.urun,kodlar=data.kod,tipler=data.tip,sktler=data.skt,etiketler=data.etiket,daralar=data.dara,birim_gramajlar=data.birim_gramaj,barkod_formatlar=data.barkod_format,mesajlar=data.msg;
let filteredIndexes=[],deleteIndex=-1,currentPage=1,perPage=10;

function applyFilters(){
  const s = document.getElementById('searchInput')?.value.toLowerCase() || '';
  filteredIndexes = [];

  for (let i = 0; i < urunler.length; i++) {
    if (kodlar[i].toLowerCase().includes(s) || urunler[i].toLowerCase().includes(s)) {
      filteredIndexes.push(i);
    }
  }

  // Eğer arama kutusu boşsa ve filtreleme sıfır sonuç döndüyse tümünü ekle
  if (filteredIndexes.length === 0 && s === '') {
    for (let i = 0; i < urunler.length; i++) filteredIndexes.push(i);
  }

  renderTable();
}


function renderTable(){
  const tbody = document.querySelector('#urunTablo tbody');
  tbody.innerHTML = '';

  // 0 numaralı özel başlık satırı
  const tr0 = document.createElement('tr');
  tr0.style.backgroundColor = '#ffeaa7';
  tr0.innerHTML = `
    <td>0</td>
    <td></td>
    <td></td>
    <td><strong>${urunler[0]}</strong></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td>
      <button class='action edit' onclick='editProduct(0)'>✏️</button>
    </td>`;
  tbody.appendChild(tr0);

  // Normal ürünler (1'den itibaren)
  const start = (currentPage - 1) * perPage;
  const end = Math.min(start + perPage, filteredIndexes.length);
  let sira = start + 1; // 🔧 burada 1’den başlıyoruz
  
  for (let j = start; j < end; j++) {
    const i = filteredIndexes[j];

    // 0 numaralı ürünü atla (çünkü onu yukarıda manuel çizdik)
    if (i === 0) continue;

    const tr = document.createElement('tr');
    tr.innerHTML = `
      <td>${sira}</td>
      <td><input type='checkbox' class='rowCheck' data-i='${i}'></td>
      <td>${kodlar[i]}</td>
      <td>${urunler[i]}</td>
      <td>${tipler[i] == 0 ? 'AĞIRLIK' : 'ADET'}</td>
      <td>${sktler[i]}</td>
      <td>${etiketDosyalari[etiketler[i]] || '❓'}</td>
      <td>${daralar[i]}</td>
      <td>${birim_gramajlar[i]}</td>
      <td>${barkod_formatlar[i]}</td>
      <td>${mesajlar[i]}</td>
      <td>
        <button class='action edit' onclick='editProduct(${i})'>✏️</button>
        <button class='action delete' onclick='openDeleteModal(${i})'>🗑️</button>
      </td>`;
    tbody.appendChild(tr);
    sira++;
  }

  // Sayfa bilgisi
  pageInfo.textContent = `${currentPage}/${Math.ceil(filteredIndexes.length / perPage) || 1}`;
  prevPage.disabled = currentPage === 1;
  nextPage.disabled = currentPage >= Math.ceil(filteredIndexes.length / perPage);
}


function editProduct(i){
  editIndex.value = i;
  kod.value = kodlar[i];
  isim.value = urunler[i];
  tip.value = tipler[i];
  skt.value = sktler[i];
  etiket.value = etiketler[i]; // hidden input
  document.getElementById('etiketSelect').value = etiketler[i];
  dara.value = daralar[i];
  birimGramaj.value = birim_gramajlar[i];
  barkodFormat.value = barkod_formatlar[i];
  mesajInput.value = mesajlar[i];      // <-- Önemli düzeltme
  msg.textContent = `✏️ Düzenleme: ${kodlar[i]}`; // Bu yukarıdaki mesaj div'i için
  kod.scrollIntoView({behavior: 'smooth', block: 'center'});
  kod.focus();
}



function openDeleteModal(i){
  if (i === 0) return;
  deleteIndex=i;
  deleteText.textContent=`${kodlar[i]} numaralı ürünü sıfırlamak istiyor musunuz?`;
  deleteModal.style.display='flex';
}
cancelDelete.onclick=()=>{deleteModal.style.display='none';deleteIndex=-1;};
confirmDelete.onclick = async () => {
  if (deleteIndex <= 0) return;
  urunler[deleteIndex] = 'Urun' + kodlar[deleteIndex];
  tipler[deleteIndex] = 0;
  sktler[deleteIndex] = 0;
  etiketler[deleteIndex] = 0;
  daralar[deleteIndex] = 0.0;
  birim_gramajlar[deleteIndex] = 0.0;
  barkod_formatlar[deleteIndex] = 0;
  mesajlar[deleteIndex] = '';

  // **Önce kapat**
  deleteModal.style.display = 'none';
  deleteIndex = -1;

  // Sonra işlemleri yap
  await saveData();
  applyFilters();
  msg.textContent = '✅ Ürün sıfırlandı!';
};


productForm.onsubmit=async e=>{
  e.preventDefault();
  const idx=editIndex.value.trim();
  const etiketIndex = +document.getElementById('etiketSelect').value;

  if(kod.value.trim()===''){alert('Kod boş');return;}

  if(idx===''){
    kodlar.push(kod.value);
    urunler.push(isim.value);
    tipler.push(+tip.value);
    sktler.push(+skt.value);
    etiketler.push(etiketIndex);
    daralar.push(parseFloat(dara.value) || 0.0);
    birim_gramajlar.push(parseFloat(birimGramaj.value) || 0.0);
    barkod_formatlar.push(+barkodFormat.value || 0);
    mesajlar.push(mesajInput.value);
  }else{
    const i=+idx;
    kodlar[i]=kod.value;
    urunler[i]=isim.value;
    tipler[i]=+tip.value;
    sktler[i]=+skt.value;
    etiketler[i]=etiketIndex;
    daralar[i]=parseFloat(dara.value);
    birim_gramajlar[i]=parseFloat(birimGramaj.value);
    barkod_formatlar[i]=+barkodFormat.value;
    mesajlar[i]=mesajInput.value;
  }

  await saveData();
  productForm.reset();
  document.getElementById('etiketSelect').value = "0";
  editIndex.value='';
  applyFilters();
  msg.textContent='✅ Ürün kaydedildi!';
  kod.focus();
};


async function saveData(){
  const resp = await fetch('/saveproduct', {
    method:'POST',
    headers:{'Content-Type':'application/json'},
    body: JSON.stringify({urun:urunler,kod:kodlar,tip:tipler,skt:sktler,etiket:etiketler,dara:daralar,birim_gramaj:birim_gramajlar,barkod_format:barkod_formatlar,msg:mesajlar})
  });
  if (!resp.ok) {
    alert('❌ Kayıt işlemi başarısız! Sunucu: ' + resp.status);
    throw new Error('Kayıt başarısız');
  }
}

prevPage.onclick=()=>{if(currentPage>1){currentPage--;renderTable();}};
nextPage.onclick=()=>{if(currentPage<Math.ceil(filteredIndexes.length/perPage)){currentPage++;renderTable();}};
searchInput.oninput=applyFilters;

exportBtn.onclick = () => {
  let csv = 'Kod;İsim;Tip;SKT;Etiket\n';
  filteredIndexes.forEach(i => {
    const etiketAdi = etiketDosyalari[etiketler[i]] || '❓';
    csv += `${kodlar[i]};${urunler[i]};${tipler[i]==0?'AĞIRLIK':'ADET'};${sktler[i]};${etiketAdi};${daralar[i]};${birim_gramajlar[i]};${barkod_formatlar[i]};${mesajlar[i]}\n`;

  });
  const blob = new Blob([csv], { type: 'text/csv' });
  const a = document.createElement('a');
  a.href = URL.createObjectURL(blob);
  a.download = 'urunler.csv';
  a.click();
};

pdfBtn.onclick=()=>{
  const {jsPDF}=window.jspdf;
  const doc=new jsPDF();
  let y=10;doc.setFontSize(12);
  filteredIndexes.forEach(i=>{
    doc.text(`${kodlar[i]} | ${urunler[i]} | ${tipler[i]==0?'AĞIRLIK':'ADET'} | ${sktler[i]} | ${etiketler[i]} | ${daralar[i]}`,10,y);
    y+=8;if(y>280){doc.addPage();y=10;}
  });
  doc.save('urunler.pdf');
};

bulkDeleteBtn.onclick=async()=>{
  const checked=[...document.querySelectorAll('.rowCheck:checked')].map(c=>+c.dataset.i);
  if(checked.length<1){alert('Hiç ürün seçilmedi');return;}
  if(confirm(`${checked.length} ürünü sıfırlamak istiyor musunuz?`)){
    checked.forEach(i=>{
      urunler[i]='Urun'+kodlar[i];
      tipler[i]=0;
      sktler[i]=0;
      etiketler[i]=0;
      daralar[i]=0.0;
      birim_gramajlar[i]=0.0;
      barkod_formatlar[i]=0;
      mesajlar[i]='';  // mesajı temizle
    });
    await saveData();
    applyFilters();
    msg.textContent='✅ Seçili ürünler sıfırlandı!';
  }
};
applyFilters();

mesajInput.addEventListener('input', () => {
  if (mesajInput.value.length > 32) {
    alert('Mesaj en fazla 32 karakter olabilir!');
    mesajInput.value = mesajInput.value.slice(0, 32);
  }
});

</script>
)rawliteral"));

  sendHeadandTail_stdtemplate(_TAIL);
  TXBuffer.endStream();
}

void handle_saveProduct() {
 // Tarayıcıdan JSON ham veri "plain" argümanında gelir
  if (web_server.hasArg("plain")) {
    String jsonData = web_server.arg("plain");

    File file = tryOpenFile("/urun.json", FILE_WRITE);
    if (!file) {
      Serial.println("❌ /urun.json açılamadı!");
      web_server.send(500, "text/plain", "Dosya açma hatası");
      return;
    }

    file.print(jsonData);
    file.close();

    Serial.println("✅ urun.json dosyası güncellendi");
    web_server.send(200, "text/plain", "OK");
  } else {
    web_server.send(400, "text/plain", "Eksik veri");
  }
}

/*// ✔ Silmek yerine varsayılanlara döndür
void handle_deleteProduct() {
  if (!isLoggedIn()) { return; }
  if (!isLisansIn()) { return; }

  int index = webArg(F("index")).toInt();
  File file = tryOpenFile(F("/urun.json"), "r");
  DynamicJsonDocument doc(32000);
  if (file) { deserializeJson(doc, file); file.close(); }

  JsonArray urunler       = doc["urun"];
  JsonArray kodlar        = doc["kod"];
  JsonArray tipler        = doc["tip"];
  JsonArray sktler        = doc["skt"];
  JsonArray etiketler     = doc["etiket"];
  JsonArray daralar       = doc["dara"];
  JsonArray birim_gramajlar = doc["birim_gramaj"];
  JsonArray barkod_formatlar = doc["barkod_format"];
  JsonArray mesajlar         = doc["msg"];

  if (index >= 0 && index < (int)urunler.size()) {
    // silmek yerine sıfırla
    urunler[index]       = String(F("Urun")) + kodlar[index].as<String>();
    tipler[index]        = 0;
    sktler[index]        = 0;
    etiketler[index]     = 0;
    daralar[index]          = 0.0;
    birim_gramajlar[index]  = 0.0;
    barkod_formatlar[index] = 0;
    mesajlar[index]         = "";  // mesajı temizle
  }

  File f = tryOpenFile(F("/urun.json"), "w");
  serializeJson(doc, f);
  f.close();

  TXBuffer.startStream();
  sendHeadandTail_stdtemplate(_HEAD);
  addHtml(F("<h3>Ürün varsayılanlara döndürüldü!</h3><a class='button link' href='/urunler'>Geri Dön</a>"));
  sendHeadandTail_stdtemplate(_TAIL);
  TXBuffer.endStream();
}*/

/*// Düzenleme formunu otomatik doldurur
void handle_editProduct() {
  if (!isLoggedIn()) { return; }
  if (!isLisansIn()) { return; }

  int index = webArg(F("index")).toInt();

  // JSON oku
  File file = tryOpenFile(F("/urun.json"), "r");
  DynamicJsonDocument doc(32000);
  if (file) {
    deserializeJson(doc, file);
    file.close();
  }

  JsonArray urunler       = doc["urun"];
  JsonArray kodlar        = doc["kod"];
  JsonArray tipler        = doc["tip"];
  JsonArray sktler        = doc["skt"];
  JsonArray etiketler     = doc["etiket"];
  JsonArray daralar          = doc["dara"];
  JsonArray birim_gramajlar  = doc["birim_gramaj"];
  JsonArray barkod_formatlar = doc["barkod_format"];
  JsonArray mesajlar         = doc["msg"];


  // Seçilen ürünün mevcut bilgilerini al
  String kod_value           = (index >= 0 && index < (int)kodlar.size())        ? kodlar[index].as<String>()    : "";
  String isim_value          = (index >= 0 && index < (int)urunler.size())       ? urunler[index].as<String>()   : "";
  String tip_value           = (index >= 0 && index < (int)tipler.size())        ? String(tipler[index].as<int>()) : "0";
  String skt_value           = (index >= 0 && index < (int)sktler.size())        ? String(sktler[index].as<int>()) : "0";
  String etiket_value        = (index >= 0 && index < (int)etiketler.size())     ? String(etiketler[index].as<int>()) : "0";
  String dara_value          = (index >= 0 && index < (int)daralar.size())          ? String(daralar[index].as<float>(), 2) : "0.00";
  String birim_gramaj_value  = (index >= 0 && index < (int)birim_gramajlar.size())  ? String(birim_gramajlar[index].as<float>(), 2) : "0.00";
  String barkod_format_value = (index >= 0 && index < (int)barkod_formatlar.size()) ? String(barkod_formatlar[index].as<int>()) : "0";
  String mesaj_value         = (index >= 0 && index < (int)mesajlar.size())         ? mesajlar[index].as<String>() : "";
  
  TXBuffer.startStream();
  sendHeadandTail_stdtemplate(_HEAD);

  addFormHeader(F("Ürün Düzenleme"));
  addHtml(F("<form method='GET' action='/saveproduct'>"));
  addHtml(F("<input type='hidden' name='editIndex' value='")); addHtmlInt(index); addHtml(F("'>"));
  addHtml(F("Kod: <input type='text' name='kod' value='")); addHtml(kod_value); addHtml(F("'><br>"));
  addHtml(F("İsim: <input type='text' name='isim' value='")); addHtml(isim_value); addHtml(F("'><br>"));
  addHtml(F("Tip: <input type='number' name='tip' value='")); addHtml(tip_value); addHtml(F("'><br>"));
  addHtml(F("SKT: <input type='number' name='skt' value='")); addHtml(skt_value); addHtml(F("'><br>"));
  addHtml(F("Etiket: <input type='number' name='etiket' value='")); addHtml(etiket_value); addHtml(F("'><br>"));
  addHtml(F("Dara (g): <input type='number' name='dara' step='0.01' value='")); addHtml(dara_value); addHtml(F("'><br>"));
  addHtml(F("Birim Gramaj (g): <input type='number' name='birim_gramaj' step='0.01' value='")); addHtml(birim_gramaj_value); addHtml(F("'><br>"));
  addHtml(F("Barkod Formatı: <select name='barkod_format' value='")); addHtml(barkod_format_value); addHtml(F("'>"));
  addHtml(F("Mesaj: <input type='text' name='mesaj' value='")); addHtml(mesaj_value); addHtml(F("'><br>"));

  addSubmitButton();
  html_end_form();

  addHtml(F("<p><a class='button link' href='/urunler'>İptal</a></p>"));

  sendHeadandTail_stdtemplate(_TAIL);
  TXBuffer.endStream();
}*/

