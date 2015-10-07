<?php
    // configuration
require("../includes/config.php");


// if form was submitted  -- validate and insert int database
if ($_SERVER["REQUEST_METHOD"] == "POST")
{
        // validate submission
        if (empty($_POST["username"]))
        {
            apologize("You must provide a username.");
        }
        
                if (empty($_POST["username"]))
        {
            apologize("You must provide a username.");
        }
        
        else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Password missmatch.");
        }
        
        if (query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)", $_POST["username"], crypt($_POST["password"])) === false)
        {
            apologize("Username allready taken.");
            
        }
        
        else
        {
            $rows = query("SELECT LAST_INSERT_ID() AS id");
            $_SESSION["id"] = $rows[0]["id"];
            redirect("index.php");
        }
        
        
}  

 // else render form
else
{
   
    render("register_form.php", ["title" => "Register"]);
}
?>
