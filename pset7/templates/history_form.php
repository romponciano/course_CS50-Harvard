<table class="table">

    <thead>
        <tr>
            <th>Transaction Type</th>
            <th>Date/Time</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
    </thead>


    <tbody>
    <?php
            foreach ($table as $row)    
        {   
            echo("<tr>");
            echo("<td>" . $row["transaction"] . "</td>");
            echo("<td>" . date('d/m/y, g:i A',strtotime($row["date"])) . "</td>");
            echo("<td>" . $row["symbol"] . "</td>");
            echo("<td>" . $row["shares"] . "</td>");
            echo("<td>$" . number_format($row["price"], 2) . "</td>");
            echo("</tr>");
        }
    ?>

    <tr>
        <td class="hello" colspan="4"><strong>CASH</strong></td>
        <td class="hello"><strong>$<?=number_format($cash[0]["cash"], 2)?></strong></td>
    </tr>

    </tbody>
    
</table>

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
