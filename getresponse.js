window.onload = function () {

  var hints = document.getElementsByClassName('gr-hint');

  for (var i = 0; i < hints.length; i++) {
    hints[i].onclick = function () {
      document.getElementById(this.getAttribute('href').substring(1, 30)).classList.toggle('hidden');

      return false;
    }
  }

  if (document.getElementById('gr-disconnect-btn')) {
    document.getElementById('gr-disconnect-btn').onclick = function () {
      document.getElementById('gr-disconnect-modal').classList.toggle('hidden');
      return false;
    };

    document.getElementById('gr-disconnect-confirm').onclick = function () {
      window.location = document.getElementById('gr-disconnect-btn').href;
      return false;
    };
  }

  if (document.getElementById('gr-stay-connected')) {
    document.getElementById('gr-stay-connected').onclick = function () {
      document.getElementById('gr-disconnect-modal').classList.toggle('hidden');
      return false;
    };
  }

  if (document.getElementById('gr-connect')) {
    document.getElementById('gr-connect').href = 'javascript:document.getElementById(\'getresponse-admin\').submit();';
    document.getElementById('gr-connect').onclick = function () {
      if (this.className.match(/\bgr-btn-disable\b/)) {
        return false;
      }

      document.getElementById('getresponse-admin').submit();
      return false;
    };
  }

  document.getElementById('edit-getresponse-api-key').onchange = function () {
    if (this.value == '') {
      if (document.getElementById('gr-connect')) {
        document.getElementById('gr-connect').classList.add('gr-btn-disable');
      }
      if (document.getElementById('edit-submit')) {
        document.getElementById('edit-submit').classList.add('gr-btn-disable');
      }

      var buttons = document.getElementsByClassName('gr-btn-disable');
      for (var x = 0, length = buttons.length; x < length; x++) {
        buttons[x].onclick = function() {
          if (this.className.match(/\bgr-btn-disable\b/)) {
            return false;
          }
        }
      }
    } else {
      if (document.getElementById('gr-connect')) {
        document.getElementById('gr-connect').classList.remove('gr-btn-disable');
      }
      if (document.getElementById('edit-submit')) {
        document.getElementById('edit-submit').classList.remove('gr-btn-disable');
      }
    }
  };

  document.getElementById('edit-getresponse-api-key').onkeyup = function () {
    document.getElementById('edit-getresponse-api-key').onchange();
  };

  document.getElementById('edit-getresponse-api-key').onchange();

  if (document.getElementById('edit-getresponse-api-key').value != '' &&
      document.getElementById('edit-getresponse-api-key').className !== 'form-text error'
  ) {
    document.getElementById('edit-submit').className = 'form-submit gr-btn-display';
  }
};
