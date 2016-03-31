import Foundation




class BlynkClient {
    struct Constants {
        static let uriString = "http://cloud.blynk.cc:8080/3b8dfe66343d4a02a41809810fac010d/pin/"
    }
    
    
    func getPin(pin: String, completion: ((Int) -> Void)!) {
        let uri  = NSURL(string: Constants.uriString + pin)!
        let request = NSMutableURLRequest(URL: uri)
        request.setValue("application/json", forHTTPHeaderField: "Content-Type")
        request.HTTPMethod = "GET"
        Alamofire.request(request)
            .responseString { response in
                // do whatever you want here
                switch response.result {
                case .Failure(let error):
                    print(error)
                case .Success(let responseObject):
                    completion(Int(responseObject)!)
                }
        }
    }
    
    func writePin(pin: String, value: Int16) {
        let uri  = NSURL(string: Constants.uriString + pin)!
        let request = NSMutableURLRequest(URL: uri)
        request.HTTPMethod = "PUT"
        request.setValue("application/json", forHTTPHeaderField: "Content-Type")
        let stringValue = [NSString(format: "%i", value)]
        request.HTTPBody = try! NSJSONSerialization.dataWithJSONObject(stringValue, options: [])
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

}