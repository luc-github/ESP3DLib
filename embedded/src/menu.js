function initMenus() {
  document.getElementById("FWLink").addEventListener("click", function () {
    window.open("https://github.com/MarlinFirmware/Marlin", "_blank");
  });

  document.getElementById("UiLink").addEventListener("click", function () {
    window.open("https://github.com/luc-github/ESP3D-WEBUI/tree/3.0", "_blank");
  });

  document.getElementById("hlpLink").addEventListener("click", function () {
    window.open("https://github.com/luc-github/ESP3DLib/wiki", "_blank");
  });
}

export { initMenus };
