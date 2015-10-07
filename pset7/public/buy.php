<?php
    
    // configuration 
    require("../includes/config.php");   
    
    // if form is submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // if symbol or shares empty
        if (empty($_POST["symbol"]) || empty($_POST["shares"]))
        {
            // apologize
            apologize("You must enter a stock symbol and quantity of shares to buy.");
        }
        
        // if symbol is invalid
        if (lookup($_POST["symbol"]) === false)
        {
            // apologize
            apologize("Invalid stock symbol.");
        }
        
        // if shares is invalid (not a whole positive integer)
        if (preg_match("/^\d+$/", $_POST["shares"]) == false)
        {
            // apologize
            apologize("You must enter a whole, positive integer.");
        }
        
        // transaction type for history
        $transaction = 'BUY';
        
        
        $stock = lookup($_POST["symbol"]);
        
        // calculate total cost (stock's price * shares)
        $cost = $stock["price"] * $_POST["shares"];
        
        
        $cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);  
        
       
        if ($cash < $cost)
        {
            // apologize
            apologize("You can't afford this purchase.");
        }         
        
        // else if user's cash >= total price (user can afford purchase)
        else
        {
            //cast to UpperCase
            $_POST["symbol"] = strtoupper($_POST["symbol"]);
                         
            
            query("INSERT INTO portfolio (id, symbol, shares) VALUES(?, ?, ?) 
                ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $_POST["symbol"], $_POST["shares"]);
            
            
            query("UPDATE users SET cash = cash - ? WHERE id = ?", $cost, $_SESSION["id"]);
            
            
            query("INSERT INTO history (id, transaction, symbol, shares, price) VALUES (?, ?, ?, ?, ?)", $_SESSION["id"], $transaction, $_POST["symbol"], $_POST["shares"], $stock["price"]);

            
            //redirect to portfolio
           redirect("/html/index.php");  
        }
    }
    
    
    else
    {
        // render buy form
        render("buy_form.php", ["title" => "Buy Form"]);
    }
    
?>
