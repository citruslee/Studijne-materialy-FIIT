/**
* UIS implementace zabezpeceneho testu
* @author Romyk 5. 4. 2010
* @version 1.0
*
* Dovoluje spustit uis test v novm modálním oknì, aby se ztí¾ilo vykopírovávání obsohu. Pracuje s pùvodním a novým oknem.
*/

/**
* Objekt safetest (sigleton) pou¾it jako jmenný prostor
*/

uis.safeTest = {};

/** 
* Promìnna pøedstavující spu¹tìné okno 
**/
uis.safeTest.safeWindow = null;

/** 
* Promìnná na zamknutí opìtovného spu¹tìní okna 
**/
uis.safeTest.lockFlag = false;

/**
* Test mo¾nosti Vytvoøení modálního okna
* @return {boolean} ano/ne
*/

uis.safeTest.isCompatible = function () {
	// test podpory metody a nebo opery (opera metodu zna, ale neumi)
	return (!window.showModalDialog || window.opera) ? 0 : 1;
}



/**
* Vytvoøení modálního okna
* @param {string} uri dokument naèítaný do okna
* @param {string} wname název okna
*/

uis.safeTest.modalWindow = function (uri, wname) {
	// spousti se z okna, ktere oznacim
	window.name = 'uisSFMain';
        var ws = {width: screen.availWidth, height: screen.availHeight};
        var w = null;
	// Spusteni klasickeho okna v problematickych prohlizecich
        if (!uis.safeTest.isCompatible()) {
                w = window.open(uri, wname, "width=" + ws.width + ",height=" + ws.height + ",menubar=no,resizable=no,status=no,toolbar=no,left=0,top=0,fullscreen");
        }
	// Spusteni modalniho okna (IE, FF3, Safari)
        else {
		// jako argumenty predavam parenWindow a windowName
                w = window.showModalDialog(uri, {parentWindow: window, windowName: wname}, "resizable:off; dialogWidth:" + ws.width + "px;dialogHeight:" + ws.height + "px");
        }
        return w;
}

/** 
* Odemknutí (pøes flag) pùvodního (parent) okna. Spou¹tí se v novém modálním oknì. Flag v pùvodním oknì nedovolí opìtovné spu¹tìní
**/

uis.safeTest.unLockTrigger = function () {
	if (window.dialogArguments) {
		window.dialogArguments.parentWindow.uis.safeTest.lockFlag = false; // odemknute spusteni
	}
}


/**
* Spu¹tení testu v modalním oknì, øe¹í i dvojité odeslání, øe¹eno odeslání klikem na odkaz
* @param {string} uri dokument naèítaný do okna
* @param {string} wname název okna
*/

uis.safeTest.runTest = function (uri, wname, incompatibleMsg) {
	// zamknu spustec
	if (!uis.safeTest.isCompatible()) {
		alert(incompatibleMsg); return;
	}	
	if (!uis.safeTest.lockFlag) {
		uis.safeTest.lockFlag = true;
		uis.safeTest.safeWindow = wname || 'Test';
		// spustím okno
		uis.safeTest.modalWindow(uri, wname);
	}
	return false;
}

/**
* Zru¹ení kontextové nabídky v testu
*/
uis.safeTest.disableContext = function () {
	jQuery(document).bind("contextmenu", function () { return false});
}

/**
* Nastavení operaci pøi stisku kláves
*/
uis.safeTest.handleKeys = function () {
	// povoleno vsude ctrl+ a ctrl- a shift+shift + shift+alt + ctrl+alt
	jQuery(document).bind("keypress", function (e) {
		var te = e.target;
		var k = e.which || e.charCode || e.keyCode;
		// na textarei a text inputu dovolim vse
		// zmeny velikosti

		if (te.tagName == 'TEXTAREA' || 
			(te.tagName == 'INPUT' && te.type == 'text') || 
			(e.ctrlKey && (k == 61 || k == 43)) || //ctrl + 
			(e.ctrlKey && k == 45)) {// ctrl -
			return true;
		}

		if (k == 116 || (e.ctrlKey && (k == 82 || k == 114))) {
			// F5, ctrl R, IE toto nedokaze
			window.location.reload();
		}
		return false;
	});
}

/**
* Nastavení operací pøi stisku tlaèítka my¹i
*/
uis.safeTest.handleMouse = function() {
  // zamezeni oznaceni textu
  jQuery(document).bind('selectstart', function() { return false; });   // Internet Explorer
  jQuery(document).bind('mousedown', function(e) {
    var te = e.target;
    if ( te.tagName == 'SELECT' || te.tagName == 'INPUT' || te.tagName == 'TEXTAREA' ) {
      return true;
    }
    return false;
  });   // ostatni
  jQuery(document).find('input, textarea').bind('click', function() { jQuery(this).focus(); });   // inputy a textarei museji jit vyplnit
}

/**
* Nahrání testu pøes ajax, pøi chybì se zavøe okno
* @param {string} uri url pro získání testu
* @param {jQuery object} form  formuláø, do kterého se vlo¾í test
*/

uis.safeTest.loadTest = function (uri, form, errorMsg) {
		jQuery.ajax({url : uri,
				success: function (data) {
					form.html(data);
				},
				error: function () {
					alert(errorMsg);
					window.onbeforeunload = null;
					window.close();
				}
		});
}

/**
* Kontrola pøístupu, musí být kompatibilní prohlí¾eè a pøedány dialogArguments
* @param {string} incompatibleMsg Zpráva pro u¾ivatele pøi nekompatibilitì
* @param {string} forbiddenMsg Zpráva pro u¾ivatele pøi neplatném pøístupu
* @throws incompatibleMsg
* @throws forbiddenMsg
*/

uis.safeTest.checkAccess = function (incompatibleMsg, forbiddenMsg) {
	// IE vraci window.external u modalniho okna, FF konstruktor [object ModalContentWindow] 
	if (!uis.safeTest.isCompatible()) {
		throw imcompatibleMsg;
	}
	//else if (!(window.external == '[object HTMLModelessDialog]' || window.constructor == '[object ModalContentWindow]')) {
		//throw forbiddenMsg;
	//}
}

/**
* Nastavení události onbeforeunload s reloadem pùvodního okna.
*/
uis.safeTest.handleUnload = function () {
	window.onbeforeunload = function () {
		if (window.opener) {
			window.opener.location.reload();
		}
		else if (window.dialogArguments) {
			window.dialogArguments.parentWindow.location.reload();	
		}
	};
}

/**
* Ukonèení testu, ziskani vysledku pres ajax
*/

uis.safeTest.handleTestSend = function ( uri ) {
        jQuery( '#testingform' ).bind( 'submit', function (event) {
		window.name = 'uisSFTest';
		jQuery( this ).attr( 'target', 'uisSFTest' );
		if (window.opener) {
                        window.opener.location.reload();
                }
                else if (window.dialogArguments) {
                        window.dialogArguments.parentWindow.location.reload();
                } 
        });
}

