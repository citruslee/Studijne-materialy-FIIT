/*
 * 2012/11/26 pøeklady pro UIS
 * T Èerník
*/
uis.translator=new function()
{
	var translate=this;
	this.translations=[];
	this.agends= {};
	this.lang="";

	this.setVersion=function(version)
	{
		this.version=version;
	}

	this.setLang=function(lang)
	{
		this.lang=lang;
	}
	//funkce inicialiujující pøeklady pro agendu
	this.load=function(balik)
	{
		//tímto se pokusím pøedejít pokusu o naètení z agendy pøedtím ne¾ je stáhlá
		$this=this;
		uis.ajax({
			url: "/js_translate/"+balik+"_"+this.lang.toLowerCase()+".JSON",
			data:
			{
				v:this.version
			},
			dataType: 'json',
			async: false,
			success:function(data)
			{
				//console.log(data);
				if(translate.translations[$this.lang.toLowerCase()]==undefined)
				{
					translate.translations[$this.lang.toLowerCase()]={};
				}
				$.extend(translate.translations[$this.lang.toLowerCase()],data);
			},
			error:function()
			{
				uis.post('/js_translate/chybejici.pl',{'balik':balik, jazyk:$this.lang, verze:$this.version});
			}
		});
	}
	/*
		Tato medoda umo¾nuje nastavit jazyk konkrétního pøekladu
	*/
	this.translateLan=function(SYSID,Lang)
	{
		Lang=Lang.toLowerCase();
		SYSID=SYSID.toLowerCase();
		if(translate.translations[Lang]==undefined)
		{
			uis.post('/js_translate/chybejici.pl',{'preklad':SYSID, jazyk:Lang, verze:this.version});
			//tady by se mohlo udìlat podobné chození jako pøi chybì pøekladù
			return SYSID;
		}else
		{
			ret=translate.translations[Lang][SYSID];
			if(ret == undefined)
			{
				uis.post('/js_translate/chybejici.pl',{'preklad':SYSID, jazyk:Lang, verze:this.version});
				return SYSID;
			}
			else
				return ret;
		}
	}
	/*
		Tato medoda prelozí danné do nastaveného jazyka SYSID
	*/
	this.translate=function(SYSID)
	{
		return translate.translateLan(SYSID,translate.lang);
	};
}

/**
 * Returns translate for specified sysid.
 * @param {string} sysid identificator
 * @param {string} defaultValue
 * @return {string} translated text
 *
 * rozsirime uis o metodu translate o snazsi pouziti
 */

uis.translate=uis.translator.translate;
