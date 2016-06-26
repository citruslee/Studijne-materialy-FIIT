/** 
* Základní JS pro UIS, zavádí prostor UIS a pracuje s jQuery 
* @author Romyk - 15. 11. 2009
*/

/**
* Základní JS "tøída" pro UIS 
* @constructor
*/
var uis = new function () {

/**
* Promìnná {array} - seznam funkcí pro spu¹tìní pøi události ready
*/
	var readyQueue =  new Array();

/**
* Metoda pro kontrolu jQuery
* @returns true/false 
*/
	this.checkJQuery = function () {
		try {
			jQuery();
			return true;
		}
		catch (e) {
			return false;
		}
	};
/**
* Metoda konvertuje selector na jQuery objekt
* @param {string} selector	jQuery selektor || DOM uzly
*/
	this.getSelector = function (selector) {
		if (!selector) {
			return null;
		}
		else { 
			return jQuery(selector);
		}
	};
/**
* Provede funkci nad v¹emi uzly - nepou¾ívat, mo¾ná do budoucna
* @param  {jquery object} nodes
* @param  {function} funcs
* @ignore
*/
	var process = function (nodes, funcs) {
	};

/**
* Vlo¾ení funkce do zásobníku pro spu¹tìní pøi události ready
* Voláni uis.readyPush(fce, par1, par2, par3);
* @param  {function} func	Funkce
* @param  {type}  par1, par2, par3, ...	Parametry funkce
*/
	this.readyPush = function () {
		var params = arguments;
		var func = params[0];
		for (var a=0; a < params.length; a++) {
			params[a] = params[a+1];
		}
		readyQueue.push([func, params]);
	};

/**
* Provede zásobník (spu¹tìní) pri události ready
*/
        this.processReadyQueue = function () {
		while (readyQueue.length) {
	                var f = readyQueue.shift();
			f[0].apply(this, f[1]); //spusteni funkce
		}
        };

/**
* Vykresleni debug okna
* @private
*/
	var debugWindow = null;
	var getDebugWindow = function () {
		if (!debugWindow) {
			debugWindow = jQuery('<div class="uisDebugWindow"><div style="background-color: gray">UIS JS Debug console</div></div>');
			debugWindow.bind('dblclick', function () {
				debugWindow.hide();
			});
			debugWindow.css({position: 'fixed', right: 0, top: 0, width: '500px', height: '300px', overflow: 'auto', 
					'background-color': 'white', border: '2px solid black', color: 'black', 'z-index': 1000000});	
			//(debugWindow.draggable && debugWindow.draggable());
			//(debugWindow.resizable && debugWindow.resizable());
			jQuery("body").append(debugWindow);
		}
		return debugWindow.show();
	};

/**
* Vypis debug okna
* @param {mixed} cokoliv pro vypsání do debug okna
*/
	var debugParam = 0;
	this.debug = function () {
		var params = arguments;
		var c = ''; //obsah k vypisu
		for (var a=0; a < params.length; a++) {
			c += '<h5>Debug parametr ' + ++debugParam + '</h5>';
			c += '<div>Konstruktor: ' + params[a].constructor + '</div>';
			//Vypis objektu
			if (typeof params[a] == 'object') {
				for (var i in params[a]) {
					c += '<div>&nbsp;&nbsp;prvek ' + i + ': ' + params[a][i] + '</div>';
				}
			}
			// Ostatni
			else {
				c += '<div>Hodnota: ' + params[a] + '</div>';
			}
                }
		d = getDebugWindow();
		d.append(c);
	};

/**
* Ziskání nadøazeného formuláøe pro libovolný prvek. Pøi zadání formu vratí sebe sama
* @param {domNode | jQuery object | selector} element
*/

	this.getParentForm = function (element) {
		if (element) {
			element = uis.getSelector(element);
			while (element.parent() && element.get(0).tagName != 'FORM') { 
                                element = element.parent();
                        }
			element = element.get(0).tagName == 'FORM' ? element : null;
		}
		return element;
	};

/**
* Získání seznamu parametrù z prvku formuláøe
* @param {domNode | jQuery object | selector} element - submit z formu nebo form. U submitu vrací i pøíslu¹ný submit. Pokud je uveden jiný element, tak se pokusí nalézt nadøazený form.
* @throws "uis.js: Neziskan element form v metode getFormParams."
* @throws "uis.js: Nepredan objekt metode getFormParams."
*/
	this.getFormParams = function (element) {
		if (!element || typeof element != 'object') {
			throw "uis.js: Nepredan objekt metode getFormParams.";
			return null;
		}
		else {
			element = jQuery(element);
			if (!element || !element.get(0)) {
				throw "uis.js: Neziskan element v metode getFormParams.";
				return null;
			}
		}
		var p = '';
		var f = element;
		if (element.get(0).tagName == 'INPUT' && element.attr('type') == 'submit') {
			p = element.attr('name') + '=' + element.val();
		}
		if (element.get(0).tagName != 'FORM') {
			// hledam form
			f = uis.getParentForm(f);
		}

		// potrebuji dale pouze formular
		if (f.get(0).tagName != 'FORM') {
			throw "uis.js: Neziskan element form v metode getFormParams.";
			return null;
		}

		var items = jQuery(f).find("input:checked, textarea, input[type='hidden'], input[type='text'], select");
		for (var i = 0; i<items.length; i++) {
			var item = items[i] ? jQuery(items[i]) : null;
			if (item && item.attr('name') && item.val()) {
				// reseni multiple select, chceme posilat ne jako p=1,2,3, ale p=1&p=2&p=3
				if (item.attr('multiple')) {
					var vals = item.val(); //.split(",");
					for (var v=0; v < vals.length; v++) {
						p += p ? '&' : '';       
						p += item.attr('name') + '=' + this.ISOEscape(vals[v]);
					}
				}
				else {
					p += p ? '&' : '';       
					p += item.attr('name') + '=' + this.ISOEscape(item.val());
				}
			}
		}
		return p;
	};


/**
* Zkrácení obsahu elementu s ikonkou na rozklik
* @param  {string} selector	Vybraný element
* @param  {number} limit	poèet znakù
* @param  {object} options - iconHide, iconShow, textHide, textShow - ikony a text pro schovani a otevreni elementu
*			   - process - rovnou zkratit 0/1
*			   - dots - vypis vypustku 0/1
*			   - words - kratit na cela slova 0/1, najde posledni ukoncene slovo pred limitem
*/
	this.shortElements = function (selector, limit, options) {
		var options = options || {};
		var limit = limit || 100;
		options.process = options.process || true;  // zkratit po vypsani
		options.iconShow = '/img.pl?sysid=' + (options.iconShow ? options.iconShow : 'small-vic'); // ikonka pro otevreni
		options.iconHide = '/img.pl?sysid=' + (options.iconHide ? options.iconHide : 'small-min'); // ikonka pro schovani
		options.dots = options.dots || true; // chceme vypustek
		options.words = options.words || true; // chceme cela slova 
		options.textHide = options.textHide || ''; //text pro schovani
		options.textShow = options.textShow || ''; //text pro otevreni
		var nodes = this.getSelector(selector);

		var iconSwitchClick = function () {
			// click na jeden nebo druhy odkaz
			jQuery(this).parent().children("span.uisShortenText, a").each(function () {
				// bohuzel elegantni toggle je v totmto pripade v IE nefunkcni
				var self = jQuery(this);
				self.css('display', self.css('display') == 'none' ? '' : 'none');
			});
			return false;
		};

		nodes.each(function() {
			var elStack = new Array(); // zásobník elementù
			var node = jQuery(this);
			var content = node.html();
			if (node.hasClass('uisShortElement') || content.replace(/<[^>]*?>/,'').length <= limit) {
				return;
			}
			node.addClass('uisShortElement');
			var content = content.split("");
			var tag = '';
			var i=0; // pocet znaku celkem 
			var c=0; // pocet znaku bez tagu
			var lastWord = 0; // konec posledniho slova

			while (c < limit && i < content.length) {	
				if (content[i] == '<') {
					tag = content[i]; i++;
					while (content[i] && content[i] != '>') {
						tag += content[i];
						i++;
					}
					tag += content[i]; i++;	
					// mam tag
					if (/^<\/[^>]*?>$/.test(tag)) {
						elStack.pop();
					}
					else if (/^<[^>]*?[^\/]>$/.test(tag)) {
						// obrazky neresim, nejde o dobre stukt. kod
						if (/^<img/.test(tag)) {
							elStack.push(tag);
						}
					}
				}
				else {
					i++;
					c++;
					if (content[i] == ' ') {
                                                lastWord = i;
                                        }
				}
			}

			// mam zpracovany retezec do stavu, kdy mam zasobnik elementu, pocet zpracovanych znaku
			// vlozim spany a ikonu 
			var closeTags = '';
			var openTags = '';
			for (var e = 0; e < elStack.length; e++) {
				openTags += elStack[e];
				closeTags += elStack[e].replace(/ [^>]*?>/, '>').replace(/</,'</');
			}
	
			//uprava obsahu elementu
			if (options.words) { i = lastWord; }


			// upravim obsah
			content = node.html();
			node.html('<span>' + content.substring(0,i) + closeTags + '</span>'); // stale zobrazeny text

			var textToCut = jQuery('<span class="uisShortenText">' + openTags + content.substring(i,content.length) + '</span>').hide(); // osekavana cast
			node.append(textToCut);

			// vytvorim odkazy, ktere se skryvani/zobrazuji podle prepinani
                        // odkryte
                        var switchHide = jQuery('<a href="">&nbsp;' + options.textHide + '<img src="' + options.iconHide + '" alt="" /></a>').hide();
                        // schovane
                        var switchShow = jQuery('<a href="">' + (options.dots ? '&hellip;' : '') + '&nbsp;' + options.textShow + '<img src="' + options.iconShow + '" alt="" /></a>');
                        
                        // nastavim ovladani
                        switchHide.bind('click', iconSwitchClick);
			switchShow.bind('click', iconSwitchClick);

			node.append(switchHide); // cast ukazovana pri otevreni (ta, co to zkrati)
			node.append(switchShow); // cast ukazovana pri skryti (ta, co to ukaze cele)
		
			if (!options.process) {
				// spust funkci na prekliknuti	
				iconSwitchClick();
			}
		});

	};

/**
* Funkce zajistí nastavení na skrývání legendy
* Pracuje s CSS tøídami uisLegendTitle a uisLegend
*/
	this.setLegendSwitches = function () {
		// vsechny legendy schovam
		jQuery("div.uisLegend").hide();
		// vyber vsechny popisky		
		jQuery("div.uisLegendTitle a").click(function (e) {
			$(this).closest('div.uisLegendTitle').next().toggle();
			return false;
		});
	};

/**
* Seznam kódù UTF-8 a ISO-8859-2 ekvivalentù, kódy ni¾¹í ne¾ 0xFE jsou stejné
* Klíèem jsou hex utf-8 kódy
*/

	var isoToUtf = {'102':'C3','103':'E3','104':'A1','105':'B1','106':'C6','107':'E6','10C':'C8','10D':'E8','10E':'CF','10F':'EF','110':'D0','111':'F0','118':'CA','119':'EA','11A':'CC','11B':'EC','139':'C5','13A':'E5','13D':'A5','13E':'B5','141':'A3','142':'B3','143':'D1','144':'F1','147':'D2','148':'F2','150':'D5','151':'F5','154':'C0','155':'E0','158':'D8','159':'F8','15A':'A6','15B':'B6','15E':'AA','15F':'BA','160':'A9','161':'B9','162':'DE','163':'FE','164':'AB','165':'BB','16E':'D9','16F':'F9','170':'DB','171':'FB','179':'AC','17A':'BC','17B':'AF','17C':'BF','17D':'AE','17E':'BE','2C7':'B7','2D8':'A2','2D9':'FF','2DB':'B2','2DD':'BD'};
        
/**
* Metoda pro konverzi retìzce na ISO-8859-2 escaped retìzec
* @param {string} s	øetìzec 
* @return {string} ISO escaped øetìzec
*/

	this.ISOEscape = function (s) {
		if (!s) {
			return "";
		}
		var r = "";
		for (var i=0; i < s.length; i++) {
			var c = s.charCodeAt(i);
			if (c > 255) { // max. kód
				c = c.toString(16).toUpperCase();
				r += isoToUtf[c] ? "%" + isoToUtf[c] : "";
			}
			else {
				r += "%" + c.toString(16).toUpperCase();
			}
		}
		return r;
	};
}

/**
* Provedení základních volání po pøipojení uis.js
*/
if (uis.checkJQuery) {
	jQuery('document').ready(function() {
		// nastav legendy
		uis.setLegendSwitches();

		// zpracuj pozadavky ve fronte
		uis.processReadyQueue();
	});
}
else {
	throw "Problem v uis.js: neni dostupne jQuery.";
};


