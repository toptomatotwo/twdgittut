
<header class="header" id="home">
    <div class="shadow"></div>
    <div class="fixed-text">
         <div class="w-container slider-container">
             <?php if(!empty($brt_block['first_text'])):?>
             <div class="first_text" data-ix="fade-from-left"><?php print $brt_block['first_text'];?></div>
             <?php endif;?>
             <?php if(isset($brt_block['enable_line']) && $brt_block['enable_line'] == 1):?>
                <div class="dots_line" data-ix="line-from-left"></div>
             <?php endif;?>

             <?php if(isset($header_content)):?>
                <?php print $header_content;?>
             <?php endif;?>

             <?php if(isset($brt_block['button_text']) && isset($brt_block['button_link'])):?>
                 <?php if(!empty($brt_block['button_text'])):?>
                    <a class="button slider" href="<?php print $brt_block['button_link'];?>" data-ix="pop-up-7"><?php print $brt_block['button_text'];?></a>
                 <?php endif;?>
             <?php endif;?>
         </div>
     </div>
     <!-- <div id="photo-credit"><a href="">Photo credit & link goes here</a></div> -->
</header>