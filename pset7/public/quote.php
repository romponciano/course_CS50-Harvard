<?php

    // configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // lookup stock info
        $_POST = lookup($_POST["symbol"]);

        if ($_POST === false)
        {
            apologize("Invalid stock symbol");
        }
        
        // else render quote_price
        render("price_form.php", ["title" => "Quote"]);

    }
    
    // else render quote_form
    else
    {
        
        render("quote_form.php", ["title" => "Quote"]);
    }

?>
