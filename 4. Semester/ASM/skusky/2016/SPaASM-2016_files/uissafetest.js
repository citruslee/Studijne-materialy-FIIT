/**
* UIS implementace zabezpeceneho testu
* @author Romyk 5. 4. 2010
* @version 1.0
*
* Dovoluje spustit uis test v novm mod�ln�m okn�, aby se zt�ilo vykop�rov�v�n� obsohu. Pracuje s p�vodn�m a nov�m oknem.
*/

/**
* Objekt safetest (sigleton) pou�it jako jmenn� prostor
*/

uis.safeTest = {};

/** 
* Prom�nna p�edstavuj�c� spu�t�n� okno 
**/
uis.safeTest.safeWindow = null;

/** 
* Prom�nn� na zamknut� op�tovn�ho spu�t�n� okna 
**/
uis.safeTest.lockFlag = false;

/**
* Test mo�nosti Vytvo�en� mod�ln�ho okna
* @return {boolean} ano/ne
*/

uis.safeTest.isCompatible = function () {
	// test podpory metody a nebo opery (opera metodu zna, ale neumi)
	return (!window.showModalDialog || window.opera) ? 0 : 1;
}



/**
* Vytvo�en� mod�ln�ho okna
* @param {string} uri dokument na��tan� do okna
* @param {string} wname n�zev okna
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
* Odemknut� (p�es flag) p�vodn�ho (parent) okna. Spou�t� se v nov�m mod�ln�m okn�. Flag v p�vodn�m okn� nedovol� op�tovn� spu�t�n�
**/

uis.safeTest.unLockTrigger = function () {
	if (window.dialogArguments) {
		window.dialogArguments.parentWindow.uis.safeTest.lockFlag = false; // odemknute spusteni
	}
}


/**
* Spu�ten� testu v modaln�m okn�, �e�� i dvojit� odesl�n�, �e�eno odesl�n� klikem na odkaz
* @param {string} uri dokument na��tan� do okna
* @param {string} wname n�zev okna
*/

uis.safeTest.runTest = function (uri, wname, incompatibleMsg) {
	// zamknu spustec
	if (!uis.safeTest.isCompatible()) {
		alert(incompatibleMsg); return;
	}	
	if (!uis.safeTest.lockFlag) {
		uis.safeTest.lockFlag = true;
		uis.safeTest.safeWindow = wname || 'Test';
		// spust�m okno
		uis.safeTest.modalWindow(uri, wname);
	}
	return false;
}

/**
* Zru�en� kontextov� nab�dky v testu
*/
uis.safeTest.disableContext = function () {
	jQuery(document).bind("contextmenu", function () { return false});
}

/**
* Nastaven� operaci p�i stisku kl�ves
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
* Nastaven� operac� p�i stisku tla��tka my�i
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
* Nahr�n� testu p�es ajax, p�i chyb� se zav�e okno
* @param {string} uri url pro z�sk�n� testu
* @param {jQuery object} form  formul��, do kter�ho se vlo�� test
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
* Kontrola p��stupu, mus� b�t kompatibiln� prohl�e� a p�ed�ny dialogArguments
* @param {string} incompatibleMsg Zpr�va pro u�ivatele p�i nekompatibilit�
* @param {string} forbiddenMsg Zpr�va pro u�ivatele p�i neplatn�m p��stupu
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
* Nastaven� ud�losti onbeforeunload s reloadem p�vodn�ho okna.
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
* Ukon�en� testu, ziskani vysledku pres ajax
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

