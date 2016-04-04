//
//  GenericSlideUIViewController.swift
//  tenda
//
//  Created by Anto on 04/04/16.
//  Copyright © 2016 Anto. All rights reserved.
//

import UIKit

class GenericSlideUIViewController: UIViewController {

    @IBAction func SlidePage(sender: AnyObject) {
        navigationController?.popViewControllerAnimated(true)
    }
}
