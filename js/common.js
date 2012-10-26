naclModule = null;  // Global application object.
statusText = 'NO-STATUSES';

function extractSearchParameter(name, def_value) {
  var nameIndex = window.location.search.indexOf(name + "=");
  if (nameIndex != -1) {
    var value = location.search.substring(nameIndex + name.length + 1);
    var endIndex = value.indexOf("&");
    if (endIndex != -1)
      value = value.substring(0, endIndex);
    return value;
  }
  return def_value;
}

function createNaClModule(name, tool, width, height) {
  var listenerDiv = document.getElementById('listener');
  var naclModule = document.createElement('embed');
  naclModule.setAttribute('name', 'nacl_module');
  naclModule.setAttribute('id', 'nacl_module');
  naclModule.setAttribute('width', width);
  naclModule.setAttribute('height',height);
  naclModule.setAttribute('src', tool + '/' + name + '.nmf');
  naclModule.setAttribute('type', 'application/x-nacl');
  listenerDiv.appendChild(naclModule);
}

function moduleDidLoad() {
  naclModule = document.getElementById('nacl_module');
}

function handleMessage(message_event) {
	var input = document.getElementById('logField');
	if(message_event.data == 'error')
		alert("Najpierw musisz rozpoczac gre");
	else if(message_event.data == 'black')
		input.innerHTML += 'aktualny gracz: czarny';
	else if(message_event.data == 'white')
		input.innerHTML += 'aktualny gracz: bialy';
	else if(message_event.data == 'start')
		;//ustawić piony
	else
		input.innerHTML += message_event.data;
  
}

function pageDidLoad(name, tool, width, height) {
  if (naclModule == null) {
    width = 0; 
    height = 0; 
    createNaClModule(name, tool, width, height)
  } else {
  }
}

//function updateStatus(opt_message) {
//  if (opt_message) {
//    statusText = opt_message; 
//  }
//  var statusField = document.getElementById('statusField');
//  if (statusField) {
//    statusField.innerHTML = statusText;
//  }
//}

