/*
 * metoda pro otevreni plovouciho okna
 * 
 */

uis.box= new function()
{
	/*
		promenné pro reference na alementy
	*/
	this._fixed_element=undefined;
	this._fixed_obsah=undefined;
	this._floating_element=undefined;
	this._allow_cache=0;
	this._cache=[];
	var $this=this;
	
	/*
		inits caching of data
	*/
	this.init_caching=function()
	{
		this._allow_cache=1;
	}

	this._get_fixed=function()
	{
		if(!this._fixed_element)
		{
			this._fixed_element=$("<div id='uisFixedBox'><div class='obsah'></div></div>").appendTo('body');
			this._fixed_element.click(function(e)
			{
				if(e.target.id == "uisFixedBox")
					$this.close_fixed();
			});
			this._fixed_obsah=$('.obsah',this._fixed_element);
		}
		return this._fixed_element;
	}

	this._get_floating=function()
	{
		if(!this._floating_element)
		{
			this._floating_element=$("<div id='uisFloatingBox'></div>").appendTo('body');
		}
		return this._floating_element;
	}

	this.open_fixed=function(id,data)
	{

		this._get_fixed();
		var cross=$("<div class='cross'></div>");
		cross.click(function(){$this.close_fixed();});
		this._fixed_obsah.html(this._prepare_data(id,data));
		this._fixed_obsah.prepend(cross);
		this._get_fixed().css("display","block");
		this._fixed_obsah.css('margin-left','-'+(parseInt(this._fixed_obsah.css('width'))/2+20)+'px');
		var top=parseInt(this._get_fixed().css('height'))-parseInt(this._fixed_obsah.css('height'));
		if(top <=0)
		{
			this._fixed_obsah.css('margin-top',0);
		}else
		{
			this._fixed_obsah.css('margin-top',(top/2+20)+'px');
		}
	}

	this._prepare_data=function(id,data)
	{
		if (!this._allow_cache || this._cache[id] == undefined)
		{
			if ( typeof data == "function")
			{
				this._cache[id]=data();
			}else
			{
				this._cache[id]=data;				
			}
		}
		return this._cache[id];
	}

	this.close_fixed=function()
	{
		this._get_fixed().css("display","none");
		this._fixed_obsah.html("");
	}

	this.open_floating=function(id,data,pos,width,height)
	{
		if(typeof height == 'undefined')
			height=10;
		width=25;

		this._get_floating().css('left',pos.left+width);
		this._get_floating().css('top',pos.top+height);
		this._get_floating().css("display","block");
		this._get_floating().addClass("loading");
		this._get_floating().html(this._prepare_data(id,data));
		this._get_floating().removeClass("loading");
	}
	this.close_floating=function()
	{
		this._get_floating().css("display","none");
		this._get_floating().html("");
	}
};
