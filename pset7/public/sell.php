<?php

    // configuration
    require("../includes/config.php");  
    
    // if form is submitted - do price checks and calculate - then update history
    if ($_SERVER["REQUEST_METHOD"] == "POST") 
    {
        // transaction type -- for history
        $transaction = 'SELL';

       
        $stock = lookup($_POST["symbol"]);
        
        $shares = query("SELECT shares FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        
        $value = $stock["price"] * $shares[0]["shares"];
        
        query("UPDATE users SET cash = cash + ? WHERE id = ?", $value, $_SESSION["id"]);

        query("DELETE FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);        
        
        query("INSERT INTO history (id, transaction, symbol, shares, price) VALUES (?, ?, ?, ?, ?)", $_SESSION["id"], $transaction, $_POST["symbol"], $shares[0]["shares"], $stock["price"]);

        // redirect to portfolio 
        redirect("/html/index.php");
    }
    
    // if form hasn't been submitted
    else
    {
        // query user's portfolio
        $rows = query("SELECT * FROM portfolio WHERE id = ?", $_SESSION["id"]); 

        // create new array to store stock symbols
        $stocks = [];

        // for each of user's stocks
        foreach ($rows as $row) 
        {   
            // save stock symbol
            $stock = $row["symbol"];
            
            // add stock symbol to the new array
            $stocks[] = $stock;       
        }    

        // render sell form
        render("sell_form.php", ["title" => "Sell Form", "stocks" => $stocks]);
    }
      

?>
