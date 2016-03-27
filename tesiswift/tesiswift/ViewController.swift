import Alamofire

import UIKit

class ViewController: UIViewController {
    private var val: Int8 = 0

    let client = BlynkClient()
    
    var timer = NSTimer.init()

    @IBOutlet var internaLight: UIProgressView!
    
    func notification() {
     //   client.getPin("V123", completion: ((value: Int) -> ()        {
     //       internaLight.progress = value
     //   }))
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        timer = NSTimer.scheduledTimerWithTimeInterval(1, target: self, selector: "notification", userInfo: nil, repeats: true)

    }
    @IBOutlet weak var up: UIButton!

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    @IBAction func changeBrightness(sender: UISlider) {
        let value = [NSString(format: "%.2f", sender.value)]
        let uri = NSURL(string: "http://cloud.blynk.cc:8080/3b8dfe66343d4a02a41809810fac010d/pin/V3")!
        let request = NSMutableURLRequest(URL: uri)
        request.HTTPMethod = "PUT"
        request.setValue("application/json", forHTTPHeaderField: "Content-Type")
        request.HTTPBody = try! NSJSONSerialization.dataWithJSONObject(value, options: [])
        Alamofire.request(request)
            .responseString { response in
                // do whatever you want here
                switch response.result {
                case .Failure(let error):
                    print(error)
                case .Success(let responseObject):
                    print(responseObject)
                }
        }
    }
    
    
    @IBAction func request(sender: UIButton) {
        Alamofire.request(.PUT, "http://cloud.blynk.cc:8080/3b8dfe66343d4a02a41809810fac010d/pin/V3").responseJSON { response in
            print(response.request)  // original URL request
            print(response.response) // URL response
            print(response.data)     // server data
            print(response.result)   // result of response serialization
            
            if let JSON = response.result.value {
                print("JSON: \(JSON)")
            }
        }
        
    }

    @IBAction func tendaDownOver(sender: AnyObject) {
        over()
    }

    @IBAction func tendaDown(sender: UIButton) {
        if (!OSAtomicTestAndSet(0, &val)) {
            client.writePin("D8", value: 0)
            client.writePin("D13", value: 0)
            client.writePin("D7", value: 255)
            client.writePin("D12", value: 255)
            setSpeed()
        }
        val = 0
    }
    
    @IBAction func tendaUp(sender: AnyObject) {
        if (!OSAtomicTestAndSet(0, &val)) {
            client.writePin("D8", value: 255)
            client.writePin("D13", value: 255)
            client.writePin("D7", value: 0)
            client.writePin("D12", value: 0)
            setSpeed()
        }
        val = 0
        
    }
    
    @IBAction func tendaUpOver(sender: AnyObject) {
        over()
    }
    
    func over() {
        client.writePin("D8", value: 0)
        client.writePin("D13", value: 0)
        client.writePin("D7", value: 0)
        client.writePin("D12", value: 0)
        client.writePin("D6", value: 255)
        client.writePin("D11", value: 255)
    }
    
    func setSpeed() {
        client.writePin("D6", value: 255)
        client.writePin("D11", value: 255)
    }
    
}


