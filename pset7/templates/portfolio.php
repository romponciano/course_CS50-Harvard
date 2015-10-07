 <?php
        $user = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
        printf("<p class=\"hello\"><br/>Hello <strong>%s</strong>.   -   Your balance is at <strong>%.2f $</strong>.</p>",$user [0]['username'], $user [0]['cash']);
        //print_r ($user);
        ?>
 
<table class="table">

    <thead>
        <tr>
                            <hr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price</th>
            <th>TOTAL</th>
        </tr>
    </thead>


    <tbody>
    <?php
            foreach ($portfolio as $row)        
        {   
            echo("<tr>");
            echo("<td>" . $row["symbol"] . "</td>");
            echo("<td>" . $row["name"] . "</td>");
            echo("<td>" . $row["shares"] . "</td>");
            echo("<td>$" . number_format($row["price"], 2) . "</td>");
            echo("<td>$" . number_format($row["total"], 2) . "</td>");
            echo("</tr>");
        }
    ?>
    <hr>
</table>
    <hr>


<br/><br/><br/><br/><hr>    <hr>

<ul class="menu">
    <a href="index.php">  Portfolio  </a> *
    <a href="quote.php">  Quote  </a> *
    <a href="buy.php">  Buy  </a> *
    <a href="sell.php">  Sell  </a> *
    <a href="history.php">  History  </a> *
    <a href="changepw.php">  Change PW  </a> *
    <a href="logout.php"><strong>  Log Out  </strong></a>
</ul>

