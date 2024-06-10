import * as React from 'react';
import { StyleSheet, View, Text } from 'react-native';
import { multiply, install} from 'react-native-bikegadget-mainapp';

const callback = (error, result) => {
  console.log('error:', error, 'result:', result);
  setHello("message from js");
}

export default function App() {
  const [result, setResult] = React.useState(multiply(4, 6));
  const [hello, setHello] = React.useState('');

  React.useEffect(() => {
    install();
    setHello(helloWorld());
    foo(callback);
    
    // callback("err123", "hello")
  }, []);

  return (
    <View style={styles.container}>
      <Text>Result: {result}</Text>
      <Text>Hello: {hello}</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
  },
  box: {
    width: 60,
    height: 60,
    marginVertical: 20,
  },
});
