<?php

function validate ($name)
{
if (substr_count($name, '"'))
  {  
  return "false";
  }
else  if (substr_count($name, '~'))
  {  
  return "false";
  }
else  if (substr_count($name, ';'))
  {  
  return "false";
  }
else  if (substr_count($name, '`'))
  {  
  return "false";
  }
else  if (substr_count($name, ':'))
  {  
  return "false";
  }
///else  if (substr_count($name, '/'))
//  {  
//  return "false";
//  }
else  if (substr_count($name, '>'))
  {  
  return "false";
  }
else  if (substr_count($name, '<'))
  {  
  return "false";
  }
else  if (substr_count($name, "'"))
  {  
  return "false";
  }
else  if (substr_count($name, '\\'))
  {  
  return "false";
  }

else
  {
  return "true";
  }
}

?>