import React, { useEffect, useState } from 'react';
import {
  SafeAreaView,
  ScrollView,
  StatusBar,
  StyleSheet,
  Text,
  useColorScheme,
  View,
  Animated,
} from 'react-native';
import { Colors } from 'react-native/Libraries/NewAppScreen';
import NativeSampleModule from './tm/NativeSampleModule';

function App(): React.JSX.Element {
  const [fuelPercentage, setFuelPercentage] = useState(0);
  const isDarkMode = useColorScheme() === 'dark';
  const backgroundStyle = {
    backgroundColor: isDarkMode ? Colors.darker : Colors.lighter,
  };

  useEffect(() => {
    NativeSampleModule.getFuelPercentage((result) => {
      setFuelPercentage(parseInt(result, 10)); // Ensure the result is an integer
    });
  }, []);

  return (
    <SafeAreaView style={backgroundStyle}>
      <StatusBar barStyle={isDarkMode ? 'light-content' : 'dark-content'} backgroundColor={backgroundStyle.backgroundColor} />
      <ScrollView contentInsetAdjustmentBehavior="automatic" style={backgroundStyle}>
        <View style={styles.container}>
          <Text style={styles.title}>Fuel Status</Text>
          <View style={styles.progressContainer}>
            <Animated.View style={[styles.progressBar, { width: `${fuelPercentage}%` }]} />
          </View>
          <Text style={styles.fuelText}>
            {`Remaining Fuel: ${fuelPercentage}%`}
          </Text>
        </View>
      </ScrollView>
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    padding: 20,
    backgroundColor: 'transparent',
  },
  title: {
    fontSize: 32,
    fontWeight: 'bold',
    marginBottom: 20,
  },
  progressContainer: {
    width: '100%',
    height: 30,
    borderRadius: 15,
    backgroundColor: Colors.lightGray,
    overflow: 'hidden',
    marginBottom: 20,
  },
  progressBar: {
    height: '100%',
    backgroundColor: Colors.primary,
    borderRadius: 15,
  },
  fuelText: {
    fontSize: 24,
    fontWeight: '600',
    color: Colors.primary,
  },
});

export default App;
