const reader = new FileReader()
let filecontent;
let endcol = 0;
let replaceContent;
let nowpos = 0;
let prvpos = 0;
let nextpos = 0;
let deletenum = 0;
let replacepostion = new Array();
function Get(input) {
    reader.readAsText(input.files[0], 'utf8') // input.files[0]为第一个文件
  reader.onload = () => {
    filecontent= reader.result
      document.getElementById("originText").innerHTML = filecontent;  // reader.result为获取结果

    }
}

function Getpos(input) {
  reader.readAsText(input.files[0], 'utf8') // input.files[0]为第一个文件
reader.onload = () => {
  replacepostion[nowpos] = reader.result
  console.log(replacepostion[nowpos])  
  }
}
function prvSelect()
{
  endcol = filecontent.indexOf("\"", replacepostion[prvpos-1]);
  replaceContent =filecontent.slice(replacepostion[prvpos-1], endcol);
  document.getElementById("content").innerHTML = replaceContent;
  nowpos--;
  prvpos--;
  nextpos--;
}

function Select()
{  
  replacepostion[nowpos] = filecontent.indexOf("English",replacepostion[prvpos]) + 10;
  endcol = filecontent.indexOf("\"", replacepostion[nowpos]);
  replaceContent =filecontent.slice(replacepostion[nowpos++], endcol);
  document.getElementById("content").innerHTML = replaceContent;
  nextpos = nowpos + 1;
  prvpos = nowpos - 1;
  //console.log(replaceContent);
  //console.log(j);
  //console.log(replacepostion[nowpos-1])
}
function replace()
{
  let input = document.getElementById("changecontent");
  console.log(input.value)
  filecontent = filecontent.replace(replaceContent, input.value);
  document.getElementById("originText").innerHTML = filecontent;
  deletenum = deletenum + (replaceContent.length) - (input.value.length)
  console.log(deletenum)
}

function Save()
{ 
  download(filecontent, "StringRelicItem-resources.assets-452.txt", "text/plain");
  download(nowpos-deletenum-100, "postion.txt", "text/plain");
}

