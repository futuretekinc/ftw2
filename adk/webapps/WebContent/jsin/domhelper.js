/**
 * Helper function to create a button, associate its onclick function and add it to specified parent.
 * 
 * @param text The button text.
 * @param onclickFn The function to associate with the button's onclick.
 * @param style The styleclass to be set on the button.
 * 
 * @returns The newly created Button.
 */
function createButton(text, onclickFn, style, id){
	var btn = createElementNode('input','',style);
	btn.type='submit';
	btn.setAttribute('value', text);
	
	btn.onclick = onclickFn;
	
	setId(btn, id);
	
	return btn;
}


/**
 * Helper function to create a DIV with the specified ID, styleclass and label;
 * and append it to specified parent.
 * 
 * All but parent are optional. An empty '' can be used if you do not want to specify 
 * a particular argument but want to provide the subsequent one.
 * 
 * @param parent The parent to which the div should be added.
 * @param id The ID of the div.
 * @param styleclass The styleclass to be set on the newly created div.
 * @param label The label for the div.
 * @param labelClass The styleclass to be set on the label.
 * 
 * @returns The newly created div.
 */
function createDiv(parent, id, styleclass, label, labelClass){
	var aDiv = createElementNode('div', id, styleclass);
	/*setId(aDiv, id);*/
	/*setClass(aDiv, styleclass);*/
	
	if(label && label != ''){
		createLabel(aDiv, id, label, labelClass);
	}
	parent.appendChild(aDiv);
	
	return aDiv;
	
}

/**
 * Helper function to create a label and associate it with a particular target element.
 * Also appends the label to the specified parent
 * 
 * @param parent The parent to which the label should be added.
 * @param targetId The ID for which this label is being set.
 * @param label The actual label text.
 * @param styleClass The styleclass to set on the label.
 * 
 *  @returns The newly created label.
 */
function createLabel(parent, targetId, label, styleClass){	
	var lbl = createElementNode('label', '', styleClass);
	lbl.setAttribute('for',targetId);
	setNodeContent(lbl, label);
	/*setClass(lbl, styleClass);*/
	parent.appendChild(lbl);
	return lbl;
}

/**
 * Helper function that creates a text box with specified ID, maxlength, styleclass.
 * The supplied function is associated with onchange, 
 * and the text box is added to its parent.
 */

function createTextBox(id, maxlen, styleclass, onchangefn){
	return int_simpleInputField('text', id, maxlen, styleclass, onchangefn);
}

function createSimplePwdBox(id, maxlen, styleclass){
	return int_simpleInputField('password', id, maxlen, styleclass);
}

function int_simpleInputField(type, id, maxlen, styleclass, onchangefn){
	var aTxt = createElementNode('input', id, styleclass);
	aTxt.type=type;
	/*setId(aTxt, id);*/
	if(maxlen && maxlen != ''){
		aTxt.setAttribute('maxlength', maxlen);
	}
	/*setClass(aTxt, styleclass);*/
	
	if(onchangefn && onchangefn != ''){
		aTxt.onchange = onchangefn;
	}
	
	/*parent.appendChild(aTxt);*/
	return aTxt;
}



/**
 * Helper function to append a dot to the specified parent.
 * The dot is wrapped in its own span.
 * 
 * @param parent - the parent node in which to place the dot.
 */
function appendDot(parent){
	parent.appendChild(createElementNode('span').appendChild(document.createTextNode('.')));
}

/**
 * Helper function to set the content of a node.
 * Attempts to use createTextNode function first.
 * If it does not exist (for example in older browsers), then falls back to innerHTML
 * 
 * @param node The node to which the text content has to be appended
 * @param content The text content to be appended
 */
function setNodeContent(node, content){
	if(isString(content)){
		if(document.createTextNode){
			node.appendChild(document.createTextNode(content));
		}else{
			node.innerHTML = content;
		}
	}
	else{
		node.appendChild(content);
	}
	
}


/**
 * Sets the content of the specified field to the supplied value.
 * @param field The field whose content needs to be set.
 * @param value The value to set.
 */
function setFieldContent(field, value){
	if(field){
		field.value = value;
	}
}


/**
 * Helper function to set a style class on an element.
 * 
 * @param element The element on which the style class needs to be applied
 * @param className The style class to be applied
 */
function setClass(element, className){
	/*
	 * Currently, this just sets className property. Could be enhanced to 
	 * 1) first check if the class is already applied to the element.
	 * 2) Add the styleclass instead of just setting it. 
	 */
	if(className && className != ''){
		element.className = className;
	}
}

/**
 * Helper function to set an ID on an element
 * @param element The element on which to set the ID
 * @param id the ID to set. If it is empty or null, it is ignored and no ID is set
 */
function setId(element, id){
	if(id && id != ''){
		if(element.id){
			element.id=id;
		}
		else{
			element.setAttribute('id', id);
		}
	}
}

/**
 * Helper function to create a new element taking into account the namespace.
 * @param elementName The name of the HTML element to be created.
 * @param id The ID for the newly created element.
 * @param style The CSS styleclass to set on the newly created element.
 * 
 * @returns The newly created element.
 */
function createElementNode(elementName, id, style){
	/*
	 * First attempts to create the element with NS (DOM createElementNS function)
	 * If not found (IE), falls back to createElement.
	 */
	var nameSpace = "http://www.w3.org/1999/xhtml";
	var newElem ;
	if(document.createElementNS){
		newElem = document.createElementNS(nameSpace, elementName);
	}else{
		newElem = document.createElement(elementName);
	}
	if(id && id != ''){
		setId(newElem, id);
	}
	
	if(style && style != ''){
		setClass(newElem, style);
	}
	
	return newElem;
}

/**
 * Helper function to create a Span element with the specified content, ID and styleclass.
 * Only content is mandatory. The other two can be blank.
 * 
 * @param content The content of the span
 * @param spanID The ID to set for the newly created Span
 * @param styleClass The CSS styleclass to set on the newly created span.
 * 
 * @returns The newly created span.
 */
function createSpan (content, spanID, styleClass){
	var aSpan = createElementNode('span', spanID,styleClass);
	/*setId(aSpan, spanID);*/
	/*setClass(aSpan, styleClass);*/
	setNodeContent(aSpan, content);
	
	return aSpan;
}

/**
 * Helper function which takes an ID and returns the String content of that field.
 * 
 * @param id The ID of the element whose content needs to be retrieved.
 * @returns The content of the specified ID.
 */
function getContentOfId(id){
	/*
	 * Mainly helpful for reducing code.
	 */
	return document.getElementById(id).value.toString();
}


/**
 * Helper function to make an inline element visible.
 * 
 * @param node The node which should be made inline visible
 */
function showInline(node){
	node.style.display = 'inline';
}

/**
 * Helper function to hide an element. Works for both block and inline elements.
 * 
 * @param node The node to be hidden
 */
function hide(node){
	node.style.display = 'none';
}

/**
 * Helper function to make a block element visible.
 * 
 * @param node The node to be made block visible.
 */
function unHide (node){
	node.style.display = 'block';
}


/**
 * Sets the content of the element with the specified ID.
 * 
 * @param id The id of the element whose content needs to be set
 * @param content The content to be set
 */
function setContentOfId(id, content){
	document.getElementById(id).value = content;
}


/*
 * Helper function to create a column.
 * 
 * If header param is true, then a TH is created, else a TD is created.
 * The rest of the params specify the parent, the content of the column 
 * and the styleclass to be applied to it.
 */

function createColumn(parent, header, content, styleClass){
	var col;
	if(header == true){
		col = createElementNode('th');
	}
	else{
		col = createElementNode('td');
	}
	if(styleClass){
		setClass(col, styleClass);
	}else{
		setClass(col, 'col');
	}
	setNodeContent(col, content);
	parent.appendChild(col);
}


/**
 * Helper function that takes an XML node as argument, 
 * and returns the content of the child node which has the specified tag.
 *  
 *  @param node The XML node with which to work.
 *  @param tagName The tag whose content needs to be retrieved.
 *  
 *  @returns the content of the child node which has the specified tag.
 * 
 *  If there are multiple children with the specified tag, 
 *  then the content of the first such tag is returned.
 */
function getTagContent(node, tagName){
	var tagElems = node.getElementsByTagName(tagName);
	if(tagElems && tagElems.length > 0 && tagElems[0].firstChild){
		return tagElems[0].firstChild.nodeValue;
	}
	else{
		return '';
	}
}



/**
 * Helper function to create a checkbox with specified name, ID, Label and the function to associate on click.
 * Also adds the checkbox to specified parent.
 * 
 * @param parent The parent to which to add the checkbox.
 * @param name The name of the checkbox.
 * @param id The ID for the checkbox.
 * @param checked boolean indicating whether the checkbox should be checked or not.
 * @param onclickfn The function to associate on click.
 * @param label Display label.
 * @param lblClass Styleclass for the display label.
 */
function createCheckBox(parent, name, id, checked, onclickfn, label, lblClass){
	var elem = createElementNode('input', id);
	elem.type='checkbox';
	/*setId(elem, id);*/
	if(name && name!=''){
		elem.setAttribute('name', name);
	}
	elem.checked = checked;
	elem.defaultChecked  = checked;
	if(onclickfn && onclickfn!=''){
		elem.onclick = onclickfn;
	}
	
	parent.appendChild(elem);
	
	if(label && label != ''){
		createLabel(parent, id, label, lblClass);
	}
	
}


/**
 * Determines whether the checkbox or radio button specified by the supplied ID is checked or not.
 * 
 * @param id The id of the checkbox or radio button to test.
 * @returns <code>true</code> if the element is selected, <code>false</code> otherwise.
 */
function isSelected(id){
	var elem = document.getElementById(id);
	if(elem.checked == true){
		return true;
	}
	else{
		return false;
	}
}

/**
 * Clears the content of a node
 * 
 * @param node The node to be cleared.
 */
function clearNode(node){
	node.innerHTML='';
}


/**
 * Creates a drop-down.
 * 
 * @param id The ID of the dropdown to be created.
 * @param style The styleclass for the drop-down to be created.
 * @returns The newly created drop-down.
 */
function createDropDown(id, style){
	var drop = createElementNode('select', id, style);
	/*setId(drop, id);*/
	/*setClass(drop, style);*/
	return drop;
}

/**
 * Adds a new drop-down item to the drop-down list.
 * @param drop The drop-down to which to add the item.
 * @param index The index at which to add the item.
 * @param value The value for the drop-down item.
 * @param dispText The text to be displayed for this item.
 * @param selected Boolean indicating whether this item should be selected in the drop-down.
 */
function addDropDownItem(drop, index, value, dispText, selected){
	/*
	var opt = createElementNode('option');
	opt.value = value;
	setNodeContent(opt, dispText);
	if(selected == true){
		opt.selected = true;
	}
	drop.options.add(opt);
	*/
	
	drop.options[index] = new Option(dispText, value, selected);
}

/**
 * Sets the specified field read-only or editable
 * @param field The field whose read-only-ness needs to be set.
 * @param ro Boolean indicating whether the field should be set read only.
 */
function setReadOnly(field, ro){
	field.readOnly = ro;
}

/**
 * Creates a Link and returns it
 * @param parent The parent node to which to add the newly created hyperlink.
 * @param id The ID of the hyperlink.
 * @param text The text to display.
 * @param onclickfn The function to call when the link is clicked.
 * @param style The styleclass to be set on the link.
 * @returns The newly created hyperlink.
 */
function createLink(parent, id, text, onclickfn, style){
	var link = createElementNode('a', id, style);
	var aDiv = createDiv(parent, '', style);
	aDiv.appendChild(link);
	
	setNodeContent(link, text);
	link.onclick = onclickfn;
	return link;
}

/**
 * Tests whether the supplied parameter is a string.
 * @param value The value to be tested.
 * @returns <code>true</code> if the value is a string, <code>false</code> otherwise.
 */
function isString(value){
	return typeof(value)=='string';
}

function createTblBody(parent, id, style){
	var tbl = createElementNode('table', id, style);
	/*setClass(tbl, style);*/
	/*setId(tbl, id);*/
	
	parent.appendChild(tbl);
	var tbody = createElementNode('tbody');
	tbl.appendChild(tbody);
	
	return tbody;
}

/**
 * Creates a radio group.
 * @param parent The parent to which the new radio button should be added.
 * @param name The name of the radio button.
 * @param value The value of the radio button.
 * @param id The ID of the radio button.
 * @param checked Boolean indicating whether the radio button should be initially checked.
 * @param onclickfn The function to associate with onlick.
 * @param label The label to be displayed for the radio button.
 * @param lblClass The styleclass to be set on the display label.
 */
function createRadio(parent, name, value, id, checked, onclickfn, label, lblClass){
	
	var elem;
	try{
		elem = document.createElement('<input type="radio" name="'+name+'" value="'+value+'" id="'+id+'" />');
	}catch(err){
		elem = createElementNode('input', id);
	}
	
	elem.type='radio';
	elem.name = name;
	elem.value = value;
		
	if(onclickfn && onclickfn!=''){
		elem.onclick = onclickfn;
	}
	
	parent.appendChild(elem);
	elem.checked = checked;
	
	if(label && label != ''){
		createLabel(parent, id, label, lblClass);
	}
}


function createTbody(id){
	var tbody = createElementNode('tbody', id);
	/*setId(tbody, id);*/
	return tbody;
}

/**
 * Creates a line break element.
 * @param parent The parent to which to add the line break.
 * @param style The styleclass to be applied on the line break.
 * @returns The newly created line break.
 */
function createBr(parent, style){
	var br = createElementNode('br', '', style);
	/*setClass(br, style);*/
	parent.appendChild(br);
	return br;
}

/**
 * Creates a new List Item (HTML li).
 * @param parent The parent to which the list item should be added.
 * @param id The ID of the list item.
 * @param style The style class to be applied on the newly created list item.
 * @param text The text to be displayed.
 * @returns The newly created list item.
 */
function createListItem(parent, id, style, text){
	var li = createElementNode('li', id, style);
	setNodeContent(li, text);
	parent.appendChild(li);
	return li;
}

/**
 * Adds a blank "line" to the specified parent.
 * @param parent The block level element where the blank line is to be added
 */
function addBlankLine(parent){
	/*
	 * TODO:
	 * 
	 * This function uses an empty HTML paragraph tag (p) to add the blank line.
	 * This is probably not the best way since we are using structural elements for doing presentation.
	 * Ideally this should be done using CSS.
	 */
	parent.appendChild(createElementNode('p'));
}

/**
 * Gets the element with specified ID, and sets its disabled state to the specified state.
 * @param elementId The Id of the element whose state has to be changed
 * @param disabledState The disabled state.
 */
function setDisabled(elementId, disabledState){
	var elem = document.getElementById(elementId);
	if(elem != null){
		elem.disabled = disabledState;
	}
}


/**
 * Finds the top-level children of the specified node, with the specified name
 * @param parent The parent (XML or HTML) node.
 * @param name The tag name to look for.
 * @returns {Array} An array of matching node elements.
 */
function getChildrenByTagName(parent, name) {
    var nodeList = [];
    for (var child = parent.firstChild; child != null; child = child.nextSibling) {
	/*
	*In IE, the Element node type is represented as NODE_ELEMENT
	* while in Mozilla it is Node.ELEMENT_NODE
	*
	* The constant value in both cases is 1.
	*/
      if (child.nodeType == 1 && name == child.nodeName) {
        nodeList.push(child);
      }
    }

    return nodeList;
}


/**
 * Creates and returns a form element with specified parameters.
 * @param name The name of the HTML form.
 * @param action The action URL.
 * @param method The HTTP method ("GET", "POST" etc)
 * @param enctype The encoding type for the form.
 * @param id The id for the form.
 * @returns {___aForm6} A form with the specified parameters.
 */
function createForm(name, action, method, enctype, id){
	var aForm = createElementNode('form', id);
	aForm.name = name;
	aForm.action = action;
	aForm.method = method;
	aForm.enctype = enctype;
	
	return aForm;
}

/**
 * Creates a File input element with the specified name.
 * @param name The name for the file input.
 * @param id The id for the file input.
 * @returns {___anInput7}
 */
function createFileInput(name, id){
	var anInput = createElementNode('input', id);
	anInput.type = 'file';
	anInput.name = name;
	
	return anInput;
}

/**
 * Removes the specified node from the DOM.
 * @param id The id of the node to be removed.
 */	
function removeElement(id) {
	var node = document.getElementById(id);
	node.parentNode.removeChild(node);
}