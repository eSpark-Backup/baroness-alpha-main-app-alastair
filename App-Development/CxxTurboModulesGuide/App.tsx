import React, { useEffect, useState } from 'react';
import {
  SafeAreaView,
  ScrollView,
  StatusBar,
  StyleSheet,
  Text,
  useColorScheme,
  View,
} from 'react-native';
import { Colors, Header } from 'react-native/Libraries/NewAppScreen';
import NativeSampleModule from './tm/NativeSampleModule';
import {RegisteredMethods} from './tm/NativeSampleModule';

function Section({ children, title }: { title: string; children: React.ReactNode }): React.JSX.Element {
  const isDarkMode = useColorScheme() === 'dark';
  return (
    <View style={styles.sectionContainer}>
      <Text
        style={[
          styles.sectionTitle,
          {
            color: isDarkMode ? Colors.white : Colors.black,
          },
        ]}
      >
        {title}
      </Text>
      <Text
        style={[
          styles.sectionDescription,
          {
            color: isDarkMode ? Colors.light : Colors.dark,
          },
        ]}
      >
        {children}
      </Text>
    </View>
  );
}

function App(): React.JSX.Element {
  const [message, setMessage] = useState(''); // State to store the message from C++
  const isDarkMode = useColorScheme() === 'dark';
  const backgroundStyle = {
    backgroundColor: isDarkMode ? Colors.darker : Colors.lighter,
  };

  useEffect(() => {
    // NativeSampleModule.install();
    NativeSampleModule.callback((result) => {
        console.log('New implementation', result);
        setMessage(result);
    })
    // Register the callback from C++ to update message state
    // RegisteredMethods.callFromCplusplus((error, result) => {
    //   if (!error) {
    //     console.log('Received from JSI Turbo Module:', result);
    //     setMessage(result); // Update the state with the result
    //   } else {
    //     console.error('Error from JSI Turbo Module:', error);
    //   }
    // });
  }, []);

  return (
    <SafeAreaView style={backgroundStyle}>
      <StatusBar barStyle={isDarkMode ? 'light-content' : 'dark-content'} backgroundColor={backgroundStyle.backgroundColor} />
      <ScrollView contentInsetAdjustmentBehavior="automatic" style={backgroundStyle}>
        <Header />
        <View
          style={{
            backgroundColor: isDarkMode ? Colors.black : Colors.white,
          }}
        >
          <Section title="Cxx TurboModule">
            NativeSampleModule.reverseString(...) ={' '}
            {NativeSampleModule.reverseString('the quick brown fox jumps over the lazy dog')}
          </Section>
          {/* Display the updated message from the callback */}
          <Section title="Callback Result">
            {message ? message : 'Waiting for callback...'}
          </Section>
        </View>
      </ScrollView>
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  sectionContainer: {
    marginTop: 32,
    paddingHorizontal: 24,
  },
  sectionTitle: {
    fontSize: 24,
    fontWeight: '600',
  },
  sectionDescription: {
    marginTop: 8,
    fontSize: 18,
    fontWeight: '400',
  },
});

export default App;
