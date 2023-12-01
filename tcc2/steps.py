import os
import torch
from tqdm import tqdm
from sklearn.metrics import f1_score, precision_recall_fscore_support, accuracy_score, classification_report

def train(model,
          data_loader, 
          val_data_loader, 
          tokenizer, 
          loss, 
          optimizer, 
          device,
          num_epochs, 
          save_path):
    """
    Implements the training and validation steps for an EntityClassifier.
    Saves best and last model at the end.

    Args:
        model: Model to be trained.
        data_loader: Training DataLoader. 
        val_data_loader: Validation DataLoader. 
        tokenizer: Tokenizer to be used with the model. 
        loss: Loss Function. 
        optimizer: Optimizer (Learning Rate is defined according to the Optimizer you pass). 
        device: Device on which the training will be conducted. (Usually cuda or cpu).
        num_epochs: Number of Epochs to train. 
        save_path: Folder to save the weights.
    """
    # Creating save folder
    os.makedirs(save_path, exist_ok=True)
    
    # Passing model to correct device
    model = model.to(device)

    # Validation Variables
    best_f1 = 0.0
    early_stop_counter = 0
    early_stop_patience = 5

    for epoch in range(num_epochs):
        # Training Step
        for inputs, labels in tqdm(data_loader):
            
            try:
                # Tokenizing
                inputs = tokenizer.batch_encode_plus(
                    inputs, 
                    padding="longest",
                    truncation=True,
                    max_length=512,
                    return_tensors="pt"
                )
            except:
                continue

            # Passing to correct device
            inputs = {k: v.to(device) for k, v in inputs.items()}
            labels = torch.tensor(labels).to(device)

            # Training
            outputs = model(**inputs, labels=labels)
            loss = outputs.loss
            loss.backward()
            optimizer.step()
            optimizer.zero_grad()
        
        # Validation Step
        with torch.no_grad():
            val_f1 = 0.0
            for val_inputs, val_labels in tqdm(val_data_loader):
                try:
                    # Tokenizing
                    val_inputs = tokenizer.batch_encode_plus(
                        val_inputs, 
                        padding="longest",
                        truncation=True,
                        max_length=512,
                        return_tensors="pt"
                    )
                except:
                    continue
                
                # Passing to correct device
                val_inputs = {k: v.to(device) for k, v in val_inputs.items()}
                val_labels = val_labels.to(device)

                # Validating
                val_outputs = model(**val_inputs)
                val_preds = torch.argmax(val_outputs.logits, axis=1)
                val_f1 += f1_score(val_labels.cpu().numpy(), val_preds.cpu().numpy(), average='macro')
            
            # Mean of Means :p
            val_f1 /= len(val_data_loader)

        print(f"Epoch {epoch+1} - Train Loss: {loss:.4f} - Val F1-Score: {val_f1:.4f}")
        
        if val_f1 > best_f1:
            best_f1 = val_f1
            early_stop_counter = 0
            torch.save(model.state_dict(), os.path.join(save_path,'best_model.pt'))
        else:
            early_stop_counter += 1
            if early_stop_counter == early_stop_patience:
                print(f"Early stopping. Best F1-Score: {best_f1:.4f}")
                break
        
        # Saving Last Model
        torch.save(model.state_dict(), os.path.join(save_path, 'last_model.pt'))

def evaluate(model,
        tokenizer,
        test_data_loader,
        device):
    """
    Runs evaluation on the given data_loader and returns the precision, recall, F1-score and accuracy of the model.
    
    Args:
        model: Trained model to be evaluated.
        tokenizer: Tokenizer to be used in the data. Compatible with the model.
        data_loader: DataLoader containing the evaluation data.
        device: Device on which to run the evaluation (usually cuda or cpu).
        
    Returns:
        A tuple containing the precision, recall, F1-score and accuracy of the model on the evaluation data.
    """
    
    # Passing model to correct device
    model = model.to(device)
    
    model.eval()
    all_preds = []
    all_labels = []

    with torch.no_grad():
        for inputs, labels in tqdm(test_data_loader):
            # Tokenizing
            inputs = tokenizer.batch_encode_plus(
                inputs,
                padding='longest',
                truncation=True,
                max_length=512,
                return_tensors='pt'
            )

            # Moving to correct device
            inputs = {k: v.to(device) for k, v in inputs.items()}
            labels = labels.to(device)

            # Forward pass
            outputs = model(**inputs)
            preds = torch.argmax(outputs.logits, axis=1)

            all_preds.extend(preds.cpu().numpy())
            all_labels.extend(labels.cpu().numpy())

    # Compute metrics
    precision, recall, f1, support = precision_recall_fscore_support(all_labels, all_preds, average='macro')
    accuracy = accuracy_score(all_labels, all_preds)
    class_report = classification_report(all_labels, all_preds, digits=4)

    return [[precision, recall, f1, accuracy], class_report]


def infer(inputs, model, tokenizer, device):
    """
    Runs an infenrence on the given data and returns model predictions.
    
    Args:
        inputs: A batch of data to infer.
        model: Trained model to be evaluated.
        tokenizer: Tokenizer to be used in the data. Compatible with the model.
        device: Device on which to run the inference (usually cuda or cpu).
        
    Returns:
        A list of model predictions, one for each input in inputs.
    """
    model = model.to(device)
    inputs = tokenizer.batch_encode_plus(
                inputs,
                padding='longest',
                truncation=True,
                max_length=512,
                return_tensors='pt'
            )

    # Moving to correct device
    inputs = {k: v.to(device) for k, v in inputs.items()}

    outputs = model(**inputs)
    preds = torch.argmax(outputs.logits, axis=1)
    classes = list(translator.keys())

    answer = ""
    for i, prob in enumerate(list(outputs.logits[0])):
        answer += str(classes[i]) + ":" + str(prob.item()) + "\n"
    
    return answer
