//
//  singleSlideUIViewController.swift
//  tenda
//
//  Created by Anto on 31/03/16.
//  Copyright © 2016 Anto. All rights reserved.
//

import UIKit


class singleSlideUIViewController: UIViewController {
    @IBOutlet weak var closedSlidebar: UIView!
    @IBOutlet weak var greenBar: UIImageView!
    @IBOutlet weak var SlidebarBtn: UIButton!
    @IBOutlet weak var SlidebarBtnGrDx: UIButton!
    
    

    
    
    @IBAction func onSlidebarBtn(sender: AnyObject) {
        UIView.animateWithDuration(0.3, delay: 0, options: UIViewAnimationOptions.CurveEaseOut, animations: { 
            self.closedSlidebar.frame.origin.x = -262
            self.SlidebarBtn.alpha = 0
            self.SlidebarBtnGrDx.alpha = 100
            }, completion: nil)
    }

    @IBAction func onSlidebarBtnDx(sender: AnyObject) {
        UIView.animateWithDuration(0.3, delay: 0, options: UIViewAnimationOptions.CurveEaseOut, animations: {
            self.closedSlidebar.frame.origin.x = 44
            self.SlidebarBtn.alpha = 100
            self.SlidebarBtnGrDx.alpha = 0
            }, completion: nil)
        
    }
    
    
}
