<form action="sell.php" method="post">
    <fieldset>
        <div class="control-group">
            <select name="symbol">
                <option value=''></option>
                <?php               
                        foreach ($stocks as $symbol)    
                    {   
                        echo("<option value='$symbol'>" . $symbol . "</option>");
                    }
                ?>
            </select>
        </div>
        <div class="control-group">
            <button type="submit" class="btn">Sell</button>
        </div>
    </fieldset>
</form>

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
